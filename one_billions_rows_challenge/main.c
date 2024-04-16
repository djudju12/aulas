#include <stdio.h>
#include <time.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <assert.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

typedef struct {
    long start, end, cursor; char *addr;
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

char keys[MAX_STATION_CNT][MAX_STATION_NAME_LEN];
Chunk chunks[4] = {0};

void make_chunks(Chunk *chunks, int how_much_chunks, const char *file_path);
int comparator(const void *a, const void *b);
int mgetline(char *station_name, char *temperature, int size, Chunk *chunk);
void process_line(Station_Table *table, char *station_name, char *temperature);

int main(void) {
    clock_t start = clock();
    // const char *file_path = "/home/jonathan/programacao/1brc/measurements-10_000.txt";
    const char *file_path = "/home/jonathan/programacao/1brc/measurements-1_000_000_000.txt";

    Chunk chunk = chunks[0];

    make_chunks(&chunk, 1, file_path);

    Station_Table *table = NULL;
    sh_new_arena(table);

    double v;
    long row = 0;
    char station_name[MAX_STATION_NAME_LEN], temperature[MAX_STATION_NAME_LEN];
    while (mgetline(station_name, temperature, 1024, &chunk) != -1) {
        if (++row % 5000000 == 0) {
            printf(FMT_CHUNK"\n", ARGS_CHUNK(chunk));
            // printf("processed %ld rows in %lf seconds\n", row, (double) (((double)clock()) - start) / CLOCKS_PER_SEC);
         }

        Station_Table *station = shgetp_null(table, station_name);
        if (station == NULL) {
            strcpy(keys[shlen(table)], station_name);
            Station_Table s = {
                .max = -99.00,
                .min = +99.00,
                .total = 0.00,
                .key = station_name
            };

            shputs(table, s);
            station = shgetp_null(table, station_name);
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

    long table_len = shlen(table);
    qsort(keys, table_len, sizeof(keys[0]), comparator);
    FILE *result = fopen("out/result.txt", "w");
    fprintf(result, "{");
    for (int i = 0; i < table_len; i++) {
        Station_Table station = shgets(table, keys[i]);
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
    int length = sb.st_size;

    char *addr = mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0);
    assert(addr != MAP_FAILED);
    close(fd);

    int offset = length / how_much_chunks;
    int end = 0;
    for (int i = 0; i < how_much_chunks; i++)  {
        chunks[i].start = end;
        end = (offset * i) + offset;
        while (end < length && addr[end] != '\n') ++end;
        chunks[i].end = end;
        chunks[i].addr = addr;
        chunks[i].cursor = 0;
    }

    if (end != length) chunks[how_much_chunks].end += (length - end);
}

int mgetline(char *station, char *temperature, int size, Chunk *chunk) {
    if (chunk->cursor >= (chunk->end - chunk->start)) return -1;
    char c = chunk->addr[chunk->start + chunk->cursor];

    int in_station = 1, lim;
    while(chunk->cursor < (chunk->end - chunk->start) && c != '\n') {
        if ( (size-1) <= lim++ ) break;
        if (c == ';') {
            *(station++) = '\0';
            in_station = 0;
            ++chunk->cursor;
            c = chunk->addr[chunk->start + chunk->cursor];
            continue;
        }

        if (in_station) {
            *(station++) = c;
        } else {
            *(temperature++) = c;
        }

        ++chunk->cursor;
        c = chunk->addr[chunk->start + chunk->cursor];
    }

    if (c == '\n') chunk->cursor++;

    return 0;
}

void process_line(Station_Table *table, char *station_name, char *temperature) {
}

int comparator(const void *a, const void *b) {
    const char (*str1)[MAX_STATION_NAME_LEN] = a;
    const char (*str2)[MAX_STATION_NAME_LEN] = b;
    return strcmp(*str1, *str2);
}
