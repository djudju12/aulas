#include <stdio.h>
#include <assert.h>
#include <time.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define MAX_STATION_CNT 50000
#define MAX_STATION_NAME_LEN 256

typedef struct {
    char *key;
    double min;
    double total;
    double max;
    int total_entries;
} Station_Data;

#define FMT_STATION "%s=(min(%.2lf), total(%.2lf), max(%.2lf), entries(%d))"
#define ARGS_STATION(key, s) (key), (s).min, (s).total, (s).max, (s).total_entries

char keys[MAX_STATION_CNT][MAX_STATION_NAME_LEN];
int comparator(const void *a, const void *b) {
    const char (*str1)[MAX_STATION_NAME_LEN] = a;
    const char (*str2)[MAX_STATION_NAME_LEN] = b;
    return strcmp(*str1, *str2);
}

int mgetline(char *station, char *temperature, int size, FILE *stream) {
    char c;
    int cnt = 0;
    c = fgetc(stream);
    int in_city = 1;
    if (c == EOF) return EOF;
    while(c != EOF && c != '\n') {
        if ((size-1) <= cnt ) break;
        if (c == ';') {
            *(station++) = '\0';
            in_city = 0;
            cnt++;
            c = fgetc(stream);
            continue;
        }

        if (in_city) {
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

int main(void) {
    const char *file_path = "/home/jonathan/programacao/1brc/measurements.txt";
    // const char *file_path = "weather_stations.csv";

    FILE *stream = fopen(file_path, "r");
    Station_Data *stations_table = NULL;

    char station_name[MAX_STATION_NAME_LEN];
    char temperature[MAX_STATION_NAME_LEN];
    double v;
    long row = 0;
    clock_t start = clock();
    while (mgetline(station_name, temperature, 1024, stream) != EOF)  {
        if (++row % 50000000 == 0) {
            printf("processed %ld rows in %f seconds\n", row, (double) (((double)clock()) - start) / CLOCKS_PER_SEC);
        }

        Station_Data station = shgets(stations_table, station_name);

        if (station.total_entries == 0) {
            station.max = -99.00;
            station.min = +99.00;
            station.total = 0.00;
            station.key = strcpy(keys[shlen(stations_table)], station_name);
        }

        station.total_entries++;

        sscanf(temperature, "%lf", &v);
        station.total = station.total + v;

        if (v < station.min) {
            station.min = v;
        }

        if (v > station.max) {
            station.max = v;
        }

        shputs(stations_table, station);
    }


    long table_len = shlen(stations_table);

    qsort(keys, table_len, sizeof(keys[0]), comparator);

    FILE *result = fopen("result.txt", "w");
    fprintf(result, "{");

    for (int i = 0; i < table_len; i++) {
        Station_Data station = stations_table[i];

        double mean = station.total / station.total_entries;
        fprintf(result, "%s=%.2lf/%.2lf/%.2lf", keys[i], station.min, mean, station.max);
        if (i < table_len-1) {
            fprintf(result, ", ");
        }
    }

    fprintf(result, "}\n");
    fprintf(stdout, "total time spent = %lf seconds\n", (double) (((double)clock()) - start) / CLOCKS_PER_SEC);
    return 0;
}

