#include <stdio.h>

#define TOTAL_CUSTOMERS 13
unsigned arrival_times[TOTAL_CUSTOMERS] = {12, 31, 63, 95, 99, 154, 198, 221, 304, 346, 411, 455, 537};
unsigned service_times[TOTAL_CUSTOMERS] = {40, 32, 55, 48, 18, 50, 47, 18, 28, 54, 40, 72, 12};
void problem1a(void) {
    printf("\n------ PROBLEM 1.a:\n");
    unsigned next = 0;
    unsigned total_served = 0;

    int serving = -1;
    unsigned arrived = 0;
    unsigned server_time = 0;
    while (total_served < TOTAL_CUSTOMERS) {
        if (serving < 0 && server_time >= arrival_times[next]) {
            serving = next;
            arrived = server_time;
            next += 1;
        } else if (serving >= 0) {
            unsigned isgone = (server_time - arrived) >= service_times[serving];
            if (isgone) {
                printf("Departure time for customer %d is %d\n", serving + 1, server_time);
                serving = -1;
                total_served += 1;
                continue;
            }
        }

        server_time += 1;
    }
}

void problem1b(void) {
    printf("\n------ PROBLEM 1.b:\n");

    unsigned next = 0;
    unsigned total_served = 0;

    int server[2];
    unsigned arrived[2];

    server[0]  = -1;
    server[1]  = -1;
    arrived[0] =  0;
    arrived[1] =  0;

    unsigned server_time = 0;
    while (total_served < TOTAL_CUSTOMERS) {
        for (int i = 0; i < 2; i++) {
            if (server[i] < 0 && server_time >= arrival_times[next]) {
                server[i] = next;
                arrived[i] = server_time;
                next += 1;
            } else if (server[i] >= 0) {
                unsigned isgone = (server_time - arrived[i]) >= service_times[server[i]];
                if (isgone) {
                    printf("Departure time for customer %d is %d\n", server[i] + 1, server_time);
                    server[i] = -1;
                    total_served += 1;
                }
            }
        }

        server_time += 1;
    }
}

void problem1c(void) {
    printf("\n------ PROBLEM 1.c:\n");
    unsigned total_serveds = 0;

    int serving = -1;
    unsigned arrived = 0;
    unsigned server_time = 0;
    while (total_serveds < TOTAL_CUSTOMERS) {
        if (serving < 0) {
            for (int i = 0; i < TOTAL_CUSTOMERS; i++) {
                if (arrival_times[i] == 0) {
                    continue;
                } else if (server_time >= arrival_times[i]) {
                    serving = i;
                } else {
                    break;
                }
            }
            arrived = server_time;
        } else if (serving >= 0) {
            unsigned finished = (server_time - arrived) >= service_times[serving];
            if (finished) {
                printf("Departure time for customer %d is %d\n", serving + 1, server_time);
                arrival_times[serving] = 0;
                serving = -1;
                total_serveds += 1;
            }
        }

        server_time += 1;
    }
}

#define max(a, b) (a > b ? a : b)
unsigned departure(an, d0, sn) {
    return max(an, d0) + sn;
}

void problem2(void) {
    printf("\n------ PROBLEM 2:\n");
    unsigned n = 0, d0 = 0;
    while (n < TOTAL_CUSTOMERS) {
        d0 = departure(arrival_times[n], d0, service_times[n]);
        printf("Departure time for customer %d is %d\n", ++n, d0);
    }
}

int main(void) {
    problem1a();
    // problem1b();
    // problem1c();
    problem2();
    return 0;
}