#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include <stdatomic.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define MAX_STATION_CNT 10000
#define MAX_STATION_NAME_LEN 256

typedef struct {
    char *key;
    double min;
    double total;
    double max;
    int total_entries;
} Station_Data;

#define FMT_STATION "%s=%.2lf/%.2lf/%2.lf"
#define ARGS_STATION(s) (s).key, (s).min, ((s).total / (s).total_entries), (s).max

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

pthread_mutex_t mutex;
Station_Data *stations_table = NULL;

void safe_shputs(Station_Data s) {
    // pthread_mutex_lock(&mutex);
    shputs(stations_table, s);
    strcpy(keys[shlen(stations_table)], s.key);
    // pthread_mutex_unlock(&mutex);
}

Station_Data * safe_shgets(char *station_name) {
    // pthread_mutex_lock(&mutex);
    Station_Data *station = shgetp_null(stations_table, station_name);
    // pthread_mutex_unlock(&mutex);
    return station;
}

void process_line(char *station_name, char *temperature) {
    double temp;

    // Station_Data *station = shgetp_null(stations_table, station_name);
    Station_Data *station = safe_shgets(station_name);

    if (station == NULL) {
        Station_Data s = {
            .max = -99.00,
            .min = +99.00,
            .total = 0.00,
            .key = station_name
        };

        safe_shputs(s);
        station = safe_shgets(station_name);
        assert(station != NULL);
    }

    station->total_entries++;

    sscanf(temperature, "%lf", &temp);
    station->total = station->total + temp;

    if (temp < station->min) {
        station->min = temp;
    }

    if (temp > station->max) {
        station->max = temp;
    }
}

typedef struct {
    char station_name[MAX_STATION_NAME_LEN];
    char temperature[MAX_STATION_NAME_LEN];
} Work;

// #define MAX_QUEUE 2500
typedef struct {
    Work *work;
    int length;
} Work_Queue;

typedef struct {
    pthread_t *thread;
    Work_Queue *queue;
} Worker;

Worker* alloc_workers(int how_much) {
    void * do_work(void *arg);
    Worker *workers = malloc(sizeof(Worker) * how_much);
    assert(workers != NULL);
    for (int i = 0; i < how_much; i++) {
        workers[i].queue = malloc(sizeof(Work_Queue));
        assert(workers[i].queue != NULL);
        workers[i].queue->length = 0;
        workers[i].thread = malloc(sizeof(pthread_t));
        assert(workers[i].thread != NULL);
        pthread_create(workers[i].thread, NULL, do_work, workers[i].queue);
    }

    return workers;
}

void push(Work_Queue *q, char *station_name, char *temperature) {
    // assert(q->length < MAX_QUEUE);
    Work w = {
        .station_name = {0},
        .temperature = {0}
    };

    strcpy(w.station_name, station_name);
    strcpy(w.temperature, temperature);
    q->work[q->length] = w;
    // printf("%s %s\n", q->work[q->length].temperature, q->work[q->length].station_name);
    q->length++;
}

Work pop(Work_Queue *q) {
    assert(q->length > 0);
    q->length = q->length - 1;
    return q->work[q->length];
}

int is_not_empty(Work_Queue *q) {
    return q->length > 0;
}

atomic_int theres_work_left;
void * do_work(void *arg) {
    Work_Queue *q = (Work_Queue *)arg;
    while (theres_work_left) {
        if (is_not_empty(q)) {
            Work w = pop(q);
            process_line(w.station_name, w.temperature);
        }
    }
}

unsigned long djb2_hash(unsigned char *str) {
    unsigned long hash = 31;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash & 0x7FFFFFFF; /* Ensure positive value */
}

Worker* choose_worker(Worker *workers, int size, int row) {
    // long h = djb2_hash(station_name);
    return &workers[row % size];
}

// const char *file_path = "/home/kopp/fontes/pessoal/1brc/measurements-10_000.txt";
const char *file_path = "/home/kopp/fontes/pessoal/1brc/measurements-1_000_000_000.txt";
const int NUMBERS_OF_CORES = 4; // todo: pegar dinamicamente

int main(void) {
    FILE *stream = fopen(file_path, "r");

    // atomic_store(&theres_work_left, 1);
    // pthread_mutex_init(&mutex, NULL);
    // sh_new_arena(stations_table);

    char station_name[MAX_STATION_NAME_LEN], temperature[MAX_STATION_NAME_LEN];
    Worker *workers = alloc_workers(NUMBERS_OF_CORES);

    long row = 0;
    clock_t start = clock();
    while (mgetline(station_name, temperature, 1024, stream) != EOF)  {
        if (++row % 50000000 == 0) {
            break;
            printf("processed %ld rows in %f seconds\n", row, (double) (((double)clock()) - start) / CLOCKS_PER_SEC);
        }

        // Worker *worker = choose_worker(workers, NUMBERS_OF_CORES, row);
        // push(worker->queue, station_name, temperature);
    }

    fprintf(stdout, "total time spent = %lf seconds\n", (double) (((double)clock()) - start) / CLOCKS_PER_SEC);

    return 0;
    atomic_store(&theres_work_left, 0);

    // for (int i = 0; i < NUMBERS_OF_CORES; i++) {
    //     fprintf(stdout, "stopping thread %d\n", i);
    //     pthread_join(*workers[i].thread, NULL);
    // }

    long table_len = shlen(stations_table);

    qsort(keys, table_len, sizeof(keys[0]), comparator);

    FILE *result = fopen("out/result.txt", "w");
    fprintf(result, "{");
    for (int i = 0; i < table_len; i++) {
        Station_Data station = shgets(stations_table, keys[i]);
        fprintf(result, FMT_STATION, ARGS_STATION(station));
        if (i < table_len-1) {
            fprintf(result, ", ");
        }
    }

    fprintf(result, "}\n");
    fprintf(stdout, "total time spent = %lf seconds\n", (double) (((double)clock()) - start) / CLOCKS_PER_SEC);
    return 0;
}

