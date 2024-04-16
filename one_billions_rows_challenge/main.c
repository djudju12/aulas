#include <stdio.h>
#include <time.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#include <assert.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

typedef struct {
    long start, end, cursor;
    char *addr;
    int id;
} Chunk;

#define FMT_CHUNK "start(%ld), end(%ld), cursor(%ld)"
#define ARGS_CHUNK(c) (c).start, (c).end, (c).cursor

typedef struct {
    char *key;
    double min;
    double total;
    double max;
    int total_entries;
} Station_Table;
#define FMT_STATION "%s=%.2lf/%.2lf/%2.lf"
#define ARGS_STATION(s) (s).key, (s).min, ((s).total / (s).total_entries), (s).max

#define MAX_STATION_CNT 10000
#define MAX_STATION_NAME_LEN 256

char keys[MAX_STATION_CNT][MAX_STATION_NAME_LEN] = {0};
#define TOTAL_WORKERS 4
Chunk chunks[TOTAL_WORKERS] = {0};
pthread_t workers[TOTAL_WORKERS] = {0};
Station_Table *tables[4];

void make_chunks(Chunk *chunks, int how_much_chunks, const char *file_path);
int comparator(const void *a, const void *b);
int mgetline(char *station_name, char *temperature, int size, Chunk *chunk);
void * process_chunck(void *arg);

clock_t start;
int main(void) {
    start = clock();
    // const char *file_path = "/home/jonathan/fontes/1brc/measurements10k.txt";
    const char *file_path = "/home/jonathan/fontes/1brc/measurements1kkk.txt";
    make_chunks(chunks, TOTAL_WORKERS, file_path);

    for (int i = 0; i < TOTAL_WORKERS; i++) {
        printf("starting chunck = "FMT_CHUNK"\n", ARGS_CHUNK(chunks[i]));
        tables[i] = NULL;
        sh_new_arena(tables[i]);
        pthread_create(&workers[i], NULL, process_chunck, &chunks[i]);
    }

    Station_Table *agg_table = NULL;
    sh_new_arena(agg_table);

    void **ret = malloc(sizeof(void*));
    for (int i = 0; i < TOTAL_WORKERS; i++) {
        pthread_join(workers[i], ret);
        int chunk_id = * ( int * ) * ret;
        for (int j = 0; j < shlen(tables[chunk_id]); j++) {
            Station_Table *entry = shgetp_null(agg_table, tables[i][j].key);
            if (entry == NULL) {
                strcpy(keys[shlen(agg_table)], tables[i][j].key);
                shputs(agg_table, tables[i][j]);
            } else {
                entry->total_entries += tables[i][j].total_entries;
                entry->total += tables[i][j].total;

                if (tables[i][j].max > entry->max) {
                    entry->max = tables[i][j].max;
                }

                if (tables[i][j].min > entry->min) {
                    entry->min = tables[i][j].min;
                }
            }
        }
    }

    fprintf(stdout, "END ALL WORKERS AFTER %lf SECONDS\n", (double) (((double)clock()) - start) / CLOCKS_PER_SEC);

    long table_len = shlen(agg_table);

    qsort(keys, table_len, sizeof(keys[0]), comparator);
    FILE *result = fopen("out/result.txt", "w");
    fprintf(result, "{");
    for (int i = 0; i < table_len; i++) {
        Station_Table station = shgets(agg_table, keys[i]);
        fprintf(result, FMT_STATION, ARGS_STATION(station));
        if (i < table_len-1) {
            fprintf(result, ", ");
        }
    }
    fprintf(result, "}\n");
    fprintf(stdout, "total time spent = %lf seconds\n", (double) (((double)clock()) - start) / CLOCKS_PER_SEC);
    return 0;
}

void make_chunks(Chunk *chunks, int how_much_chunks, const char *file_path) {
    int fd = open(file_path, O_RDONLY);
    assert(fd != -1);

    struct stat sb;
    assert(fstat(fd, &sb) != -1);
    long length = sb.st_size;

    char *addr = mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0);
    assert(addr != MAP_FAILED);
    close(fd);

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
    double v;
    char station_name[MAX_STATION_NAME_LEN], temperature[MAX_STATION_NAME_LEN];

    while (mgetline(station_name, temperature, 1024, chunk) != -1) {
        Station_Table *station = shgetp_null(tables[chunk->id], station_name);
        if (station == NULL) {
            Station_Table s = {
                .max = -99.00,
                .min = +99.00,
                .total = 0.00,
                .key = station_name
            };

            shputs(tables[chunk->id], s);
            station = shgetp_null(tables[chunk->id], station_name);
            assert(station != NULL);
        }

        station->total_entries++;

        sscanf(temperature, "%lf", &v);
        station->total = station->total + v;

        if (v < station->min) {
            station->min = v;
        }

        if (v > station->max) {
            station->max = v;
        }
    }

    fprintf(stdout, "[ %d ] END AFTER %lf SECONDS\nG", chunk->id, (double) (((double)clock()) - start) / CLOCKS_PER_SEC);

    return &chunk->id;
}

#define EOC(c) ((c).cursor >= ((c).end - (c).start))

int mgetline(char *station, char *temperature, int size, Chunk *chunk) {
    if (EOC(*chunk)) return -1;
    char c;

    int in_station = 1, lim = 0;
    while(!EOC(*chunk) && (c = chunk->addr[chunk->start + chunk->cursor++]) != '\n') {
        if ( (size-1) <= lim++ ) break;
        if (c == ';') {
            *(station++) = '\0';
            in_station = 0;
        } else {
            if (in_station) *(station++)     = c;
            else            *(temperature++) = c;
        }
    }

    *temperature = '\0';

    return 0;
}

int comparator(const void *a, const void *b) {
    const char (*str1)[MAX_STATION_NAME_LEN] = a;
    const char (*str2)[MAX_STATION_NAME_LEN] = b;
    return strcmp(*str1, *str2);
}
