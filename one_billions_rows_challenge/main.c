#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* read_file(const char* file_path) {
    FILE *f = fopen(file_path, "r");
    if (f == NULL) {
        goto ERROR;
    }
    if (fseek(f, 0, SEEK_END) != 0) {
        goto ERROR;
    }

    int size = ftell(f);
    if (size < 0) {
        goto ERROR;
    }
    rewind(f);

    char *content = malloc(sizeof(char)*size);
    int b_read = fread(content, 1, size, f);
    if (b_read != size) {
        goto ERROR;
    }

    return content;

ERROR:
    if (f) fclose(f);
    if (content) free(content);
    return NULL;
}

int mgetline(char *city, char *value, int size, FILE *stream) {
    char c;
    int cnt = 0;
    c = fgetc(stream);
    int in_city = 1;
    if (c == EOF) return EOF;
    while(c != EOF && c != '\n') {
        if ((size-1) <= cnt ) break;
        if (c == ';') {
            *(city++) = '\0';
            in_city = 0;
            cnt++;
            c = fgetc(stream);
            continue;
        }

        if (in_city) {
            *(city++) = c;
        } else {
            *(value++) = c;
        }

        cnt++;
        c = fgetc(stream);
    }

    *(value++) = '\0';
    return 0;
}

struct City_Data {
    char city[256];
    double min;
    double total;
    double max;
    int total_entries;
};

struct City_Data cities[51200] = {0};
int length = 0;

int get_city(char *symbol) {
    for (int i = 0; i < length; i++) {
        if (cities[i].total_entries > 0 && strcmp(symbol, cities[i].city) == 0) {
            return i;
        }
    }

    return -1;
}

int comparator(const void *a, const void *b) {
    return strcmp(((struct City_Data*)a)->city, ((struct City_Data *) b)->city);
}

int main(void) {
    const char *file_path = "weather_stations.csv";
    char city[256];
    char value[256];
    double v;
    FILE *stream = fopen(file_path, "r");

    while (mgetline(city, value, 1024, stream) != EOF)  {
        int index = get_city(city);
        if (index < 0) {
            index = length++;
            cities[index];
            cities[index].min = 999.0;
            cities[index].max = -999.0;
            cities[index].total = 0.0;
            int cnt = 0;
            while(city[cnt] != '\0') {
                cities[index].city[cnt] = city[cnt];
                cnt++;
            }

            cities[index].city[cnt]= '\0';
        }

        cities[index].total_entries++;
        sscanf(value, "%lf", &v);
        cities[index].total = cities[index].total + v;

        if (v < cities[index].min) {
            cities[index].min = v;
        }

        if (v > cities[index].max) {
            cities[index].max = v;
        }
    }

    qsort(cities, length, sizeof(struct City_Data), comparator);
    for (int i = 0; i < length; i++) {
        double mean = cities[i].total / cities[i].total_entries;
        printf("%-25s %+3.2lf %+3.2lf %+3.2lf\n", cities[i].city, cities[i].max, cities[i].min, mean);
        // printf("%-25s  max(%+3.2lf) min(%+3.2lf) total(%+3.2lf) entries(%02d) mean(%+3.2lf)\n", cities[i].city, cities[i].max, cities[i].min, cities[i].total, cities[i].total_entries, cities[i].total / cities[i].total_entries);
        // printf("%-25s\n",  cities[i].city);
    }

    return 0;
}

