#include "beta.h"

#if defined(LIN)

#include <string.h>
#include <sys/time.h>

typedef struct statInfo {
    struct timeval start;
    struct timeval end;
    char *func;
} statInfo;

/* LOCAL FUNCTIONS */

static void clear(statInfo *statistics);
static long member(statInfo *statistics, char *func);
static void insert(statInfo *statistics, char *func);

/* GLOBAL FUNCTIONS */
void set_start_time(char *func);
void set_end_time(char *func);
void printLinStatistics();
void initStats(void);

/* LOCAL CONSTANTS */
#define MAXSTATS 1024

/* LOCAL VARIABLES */
static statInfo statistics[MAXSTATS];

/* IMPLEMENTATION */

static void clear(statInfo *statistics) {
    long i;
    
    for (i=0;i<MAXSTATS;i++) {
        statistics[i].func = NULL;
    }
}

static long member(statInfo *statistics, char *func) {
    long i;
    
    i = 0;
    while (statistics[i].func) {
        if (strcmp(statistics[i].func,func)==0) {
            return i;
        }
        i++;
    }
    return -1;
}
    
static void insert(statInfo *statistics, char *func) {
    long i;
    
    i = 0;
    while (statistics[i].func) {
        i++;
    }
    statistics[i].func = func;
}

void initStats(void) {
    clear(statistics);
}

void set_start_time(char *func) {
    long i;
    
    if ((i = member(statistics, func)) == -1) {
        insert(statistics, func);
    }
    
    gettimeofday(&(statistics[member(statistics, func)].start), NULL);
}

void set_end_time(char *func) {
    long i;
    
    if ((i = member(statistics, func)) == -1) {
        insert(statistics, func);
    }
    
    gettimeofday(&(statistics[member(statistics, func)].end), NULL);
}

void printLinStatistics() {
    long i;
    
    i = 0;
    while (statistics[i].func) {
        long microStart, microEnd, microDiff;
        
        microStart = statistics[i].start.tv_sec * 1000000 + statistics[i].start.tv_usec;
        microEnd = statistics[i].end.tv_sec * 1000000 + statistics[i].end.tv_usec;
        
        microDiff = microEnd - microStart;
        
        printf("%30s: (usec = %10lu, sec = %4lu)\n", statistics[i].func, microDiff, microDiff/1000000);
        i++;
    }
}

#endif /* LIN */


