#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

#define MAX_STATION_CNT 10000
#define MAX_STATION_NAME_LEN 256

typedef struct {
    char key[MAX_STATION_NAME_LEN];
    double min;
    double total;
    double max;
    int total_entries;
} Station_Data;

#define FMT_STATION "%s=%.2lf/%.2lf/%2.lf"
#define ARGS_STATION(s) (s).key, (s).min, ((s).total / (s).total_entries), (s).max

int mgetline(char *station, char *temperature, int size, FILE *stream) {
    char c;
    int cnt = 0;
    c = fgetc(stream);
    int in_station = 1;
    if (c == EOF) return EOF;
    while(c != EOF && c != '\n') {
        if ((size-1) <= cnt ) break;
        if (c == ';') {
            *(station++) = '\0';
            in_station = 0;
            cnt++;
            c = fgetc(stream);
            continue;
        }

        if (in_station) {
            *(station++) = c;
        } else {
            *(temperature++) = c;
        }

        cnt++;
        c = fgetc(stream);
    }

    *(temperature++) = '\0';
    return 0;
}

#define HASHMAP_CAPACITY 16384
#define HASHMAP_INDEX(h) (h & (HASHMAP_CAPACITY - 1))
typedef struct {
    Station_Data entries[MAX_STATION_CNT];
    unsigned int table[HASHMAP_CAPACITY];
    unsigned int len;
} Hash_Map;

#include <string.h>
unsigned int *hm_get(Hash_Map *map, const char *key) {
    unsigned int len = 0;
    unsigned int h = 0;
    for (;key[len] != '\0'; len++) {
        h = (31*h) + (unsigned char)key[len];
    }

    unsigned int *c = &map->table[HASHMAP_INDEX(h)];
    while (*c > 0 && memcmp(map->entries[*c].key, key, len) != 0) {
        h++;
        c = &map->table[HASHMAP_INDEX(h)];
    }

    return c;
}

#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) > (b) ? (a) : (b)

void hm_put(Hash_Map *map, const char *key, double temperature) {
    unsigned int len = 0;
    unsigned int h = 0;
    for (;key[len] != '\0'; len++) {
        h = (31*h) + (unsigned char)key[len];
    }

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

int main(int argc, char **argv) {
    clock_t start = clock();

    char *file_path = "/home/kopp/fontes/pessoal/1brc/measurements10k.txt";
    if (argc > 1) file_path = argv[1];

    FILE *stream = fopen(file_path, "r");

    Hash_Map *map = malloc(sizeof(Hash_Map));
    memset(map->table, 0, HASHMAP_CAPACITY * sizeof(*map->table));
    memset(map->entries, 0, MAX_STATION_CNT * sizeof(*map->entries));

    long row = 0;
    double v;

    char station_name[MAX_STATION_NAME_LEN], temperature[MAX_STATION_NAME_LEN];
    while (mgetline(station_name, temperature, 1024, stream) != EOF)  {
        if (++row % 50000000 == 0) {
            printf("processed %ld rows in %f seconds\n", row, (double) (((double)clock()) - start) / CLOCKS_PER_SEC);
        }

        sscanf(temperature, "%lf", &v);
        hm_put(map, station_name, v);
    }

    qsort(map->entries, map->len, sizeof(*map->entries), comparator);

    FILE *result = fopen("out/result.txt", "w");
    fprintf(result, "{");
    for (int i = 0; i < map->len; i++) {
        Station_Data station = map->entries[i];
        fprintf(result, FMT_STATION, ARGS_STATION(station));
        if (i < map->len-1) {
            fprintf(result, ", ");
        }
    }

    fprintf(result, "}\n");
    fprintf(stdout, "total time spent = %lf seconds\n", (double) (((double)clock()) - start) / CLOCKS_PER_SEC);
    return 0;
}

