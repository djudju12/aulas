#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_STATION_CNT 10000
#define MAX_STATION_NAME_LEN 256
#define HASHMAP_CAPACITY 16384
#define HASHMAP_INDEX(h) (h & (HASHMAP_CAPACITY - 1))
#define TOTAL_WORKERS 8
#define FMT_STATION "%s=%.2lf/%.2lf/%2.lf"
#define ARGS_STATION(s) (s).key, (s).min, ((s).total / (s).total_entries), (s).max
#define FMT_CHUNK "start(%ld), end(%ld), cursor(%ld)"
#define ARGS_CHUNK(c) (c).start, (c).end, (c).cursor

#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) > (b) ? (a) : (b)

typedef struct {
    long start, end, cursor;
    char *addr;
    int id;
} Chunk;

typedef struct {
    char key[MAX_STATION_NAME_LEN];
    double min;
    double total;
    double max;
    int total_entries;
} Station_Data;

typedef struct {
    Station_Data entries[MAX_STATION_CNT];
    unsigned int table[HASHMAP_CAPACITY];
    unsigned int len;
} Hash_Map;

Chunk chunks[TOTAL_WORKERS] = {0};
pthread_t workers[TOTAL_WORKERS] = {0};

clock_t start;
#define CLOCK_DIFF(s) (double) (((double)clock()) - (s)) / CLOCKS_PER_SEC

void make_chunks(Chunk *chunks, int how_much_chunks, char *addr, long length);
int comparator(const void *a, const void *b);
int mgetline(char *station_name, char *temperature, int *h, int *len, Chunk *chunk);
void * process_chunck(void *arg);
unsigned int *hm_get(Hash_Map *map, const char *key);
void hm_put(Hash_Map *map, const char *key, double temperature, int hash, unsigned int len);

int main(int argc, char **argv) {
    start = clock();

    char *file_path = "/home/kopp/fontes/pessoal/1brc/measurements10k.txt";
    if (argc > 1) {
        file_path = argv[1];
    }

    int fd = open(file_path, O_RDONLY);
    assert(fd != -1);

    struct stat sb;
    assert(fstat(fd, &sb) != -1);
    long length = sb.st_size;

    char *addr = mmap(NULL, length, PROT_READ, MAP_SHARED, fd, 0);
    assert(addr != MAP_FAILED);

    make_chunks(chunks, TOTAL_WORKERS, addr, length);

    for (int i = 0; i < TOTAL_WORKERS; i++) {
        printf("starting chunck = "FMT_CHUNK"\n", ARGS_CHUNK(chunks[i]));
        pthread_create(&workers[i], NULL, process_chunck, &chunks[i]);
    }

    Hash_Map *results[TOTAL_WORKERS];
    for (int i = 0; i < TOTAL_WORKERS; i++) {
        pthread_join(workers[i], (void *)&results[i]);
    }

    Hash_Map *result = results[0];
    for (int i = 1; i < TOTAL_WORKERS; i++) {
        for (int k = 0; k < results[i]->len; k++) {
            unsigned int *entry = hm_get(result, results[i]->entries[k].key);
            unsigned int c = *entry;
            if (c == 0) {
                c = result->len++;
                *entry = c;
                strcpy(result->entries[c].key, results[i]->entries[k].key);
            }

            result->entries[c].max = max(result->entries[c].max, results[i]->entries[k].max);
            result->entries[c].min = min(result->entries[c].min, results[i]->entries[k].min);
            result->entries[c].total += results[i]->entries[k].total;
            result->entries[c].total_entries += results[i]->entries[k].total_entries;
        }
    }

    fprintf(stdout, "END ALL WORKERS AFTER %lf SECONDS\n", CLOCK_DIFF(start));

    qsort(result->entries, result->len, sizeof(*result->entries), comparator);
    FILE *out = fopen("out/result.txt", "w");
    fprintf(out, "{");
    for (int i = 0; i < result->len; i++) {
        Station_Data station = result->entries[i];
        fprintf(out, FMT_STATION, ARGS_STATION(station));
        if (i < result->len-1) {
            fprintf(out, ", ");
        }
    }

    fprintf(out, "}\n");
    fprintf(stdout, "total time spent = %lf seconds\n", CLOCK_DIFF(start));

    munmap((void *) addr, length);
    close(fd);
    for (int i = 0; i < TOTAL_WORKERS; i++) {
        free(results[i]);
    }

    return 0;
}

void make_chunks(Chunk *chunks, int how_much_chunks, char *addr, long length) {
    long offset = length / how_much_chunks;
    long end = 0;
    for (int i = 0; i < how_much_chunks; i++)  {
        chunks[i].start = end;
        end = (offset * i) + offset;
        while (end < length && addr[end] != '\n') ++end;
        chunks[i].end = end;
        chunks[i].addr = addr;
        chunks[i].cursor = 0;
        chunks[i].id = i;
    }

    if (end != length) chunks[how_much_chunks].end += (length - end);
}

void * process_chunck(void *arg) {
    Chunk *chunk = (Chunk *) arg;
    Hash_Map *map = malloc(sizeof(Hash_Map));

    memset(map->table, 0, HASHMAP_CAPACITY * sizeof(*map->table));
    memset(map->entries, 0, MAX_STATION_CNT * sizeof(*map->entries));

    double v; int h = 0; unsigned int len = 0;
    char station_name[MAX_STATION_NAME_LEN], temperature[MAX_STATION_NAME_LEN];
    while (mgetline(station_name, temperature, &h, &len, chunk) != -1) {
        sscanf(temperature, "%lf", &v);
        hm_put(map, station_name, v, h, len);
    }

    fprintf(stdout, "[ %d ] END AFTER %lf SECONDS\n", chunk->id, CLOCK_DIFF(start));

    return map;
}

#define EOC(c) ((c).cursor >= ((c).end - (c).start))

int mgetline(char *station, char *temperature, int *h, int *len, Chunk *chunk) {
    if (EOC(*chunk)) return -1;

    *h = 0; *len = 0;
    char c, *addr = chunk->addr + chunk->start;
    while(!EOC(*chunk) && (c = *(addr + chunk->cursor++)) != '\n' && c != ';') {
        *(station++) = c;
        *h = ((*h << 5) - *h) + (unsigned char)c;
        *len += 1;
    }

    *(station++) = '\0';

    while(!EOC(*chunk) && (c = *(addr + chunk->cursor++)) != '\n') {
        *(temperature++) = c;
    }

    *(temperature++) = '\0';

    return 0;
}

unsigned int *hm_get(Hash_Map *map, const char *key) {
    unsigned int len = 0;
    unsigned int h = 0;
    for (;key[len] != '\0'; len++) {
        h = ((h << 5) - h) + (unsigned char)key[len];
    }

    unsigned int *c = &map->table[HASHMAP_INDEX(h)];
    while (*c > 0 && memcmp(map->entries[*c].key, key, len) != 0) {
        h++;
        c = &map->table[HASHMAP_INDEX(h)];
    }

    return c;
}

void hm_put(Hash_Map *map, const char *key, double temperature, int h, unsigned int len) {
    unsigned int *c = &map->table[HASHMAP_INDEX(h)];
    while (*c > 0 && memcmp(map->entries[*c].key, key, len) != 0) {
        h++;
        c = &map->table[HASHMAP_INDEX(h)];
    }

    if (*c == 0) {
        *c = map->len;
        memcpy(map->entries[*c].key, key, len);
        map->len++;
        map->entries[*c].max = temperature;
        map->entries[*c].min = temperature;
        map->entries[*c].total = temperature;
        map->entries[*c].total_entries = 1;
    } else {
        map->entries[*c].max = max(temperature, map->entries[*c].max);
        map->entries[*c].min = min(temperature, map->entries[*c].min);
        map->entries[*c].total += temperature;
        map->entries[*c].total_entries++;
    }
}

int comparator(const void *a, const void *b) {
    return strcmp(((Station_Data *)a)->key, ((Station_Data *)b)->key);
}

