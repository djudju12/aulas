#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

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

#define MAX_STATION_CNT 51200
#define MAX_STATION_NAME_LEN 256

typedef struct {
    char station[MAX_STATION_NAME_LEN];
    double min;
    double total;
    double max;
    int total_entries;
} Station_Data;

typedef struct {
    Station_Data cities[MAX_STATION_CNT];
    char keys[MAX_STATION_CNT][MAX_STATION_NAME_LEN];
    int length;
} Station_Table;

Station_Data cities[MAX_STATION_CNT] = {0};
Station_Table stations = {0};
int length = 0;

int hash(char *key) {
    assert("TODO: int hash(char *key) NOT IMPLEMENTED");
}

Station_Data* get(char *station) {
    int index = hash(station) % MAX_STATION_CNT;
    if (stations.cities[index].total_entries > 0) {
        return &stations.cities[index];
    }

    return NULL;
}

Station_Data* new(char *station) {
    int index = hash(station) % MAX_STATION_CNT;
    if (stations.cities[index].total_entries == 0) {
        stations.cities[index].total_entries = 1;
        stations.cities[index].max = -999.00;
        stations.cities[index].min = +999.00;
        stations.cities[index].total = 0;
        strcpy(stations.keys[length++], station);
        return &stations.cities[index];
    }

    assert("Trying to create a new station on an already used index." && 0);
}

int get_city(char *symbol) {
    for (int i = 0; i < length; i++) {
        if (cities[i].total_entries > 0 && strcmp(symbol, cities[i].station) == 0) {
            return i;
        }
    }

    return -1;
}

int comparator(const void *a, const void *b) {
    return strcmp(((Station_Data*)a)->station, ((Station_Data *) b)->station);
}

int main(void) {
    const char *file_path = "/home/jonathan/programacao/1brc/measurements.txt";
    // const char *file_path = "weather_stations.csv";
    char station[MAX_STATION_NAME_LEN];
    char temperature[MAX_STATION_NAME_LEN];
    double v;
    FILE *stream = fopen(file_path, "r");

    while (mgetline(station, temperature, 1024, stream) != EOF)  {
        // int index = get_city(station);
        // if (index < 0) {
        //     index = length++;
        //     cities[index];
        //     cities[index].min = 999.0;
        //     cities[index].max = -999.0;
        //     cities[index].total = 0.0;
        //     int cnt = 0;
        //     while(station[cnt] != '\0') {
        //         cities[index].station[cnt] = station[cnt];
        //         cnt++;
        //     }

        //     cities[index].station[cnt]= '\0';
        // }

        Station_Data *station = get(station);
        if (station == NULL) {
            station = new(station);
        }

        cities[index].total_entries++;
        sscanf(temperature, "%lf", &v);
        cities[index].total = cities[index].total + v;

        if (v < cities[index].min) {
            cities[index].min = v;
        }

        if (v > cities[index].max) {
            cities[index].max = v;
        }
    }

    qsort(cities, length, sizeof(struct Station_Data), comparator);
    FILE *result = fopen("result.txt", "w");
    fprintf(result, "{");
    for (int i = 0; i < length; i++) {
        double mean = cities[i].total / cities[i].total_entries;
        fprintf(result, "%s=%+3.2lf/%+3.2lf/%+3.2lf", cities[i].station, cities[i].min, mean, cities[i].max);
        if (i < length-1) {
            fprintf(result, ", ");
        }
    }

    fprintf(result, "}\n");
    return 0;
}

