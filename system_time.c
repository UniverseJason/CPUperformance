#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>

// sample code for system time

int main(int argc, char *argv[])
{
    struct timespec ts_begin, ts_end;
    double elapsed;
    long sleep_time_ms;
    if (argc < 2)
    {
        printf("Usage: %s sleep_time_ms \n", argv[0]); return 0;
    }

    sleep_time_ms = atoi(argv[1]);
    
    printf("sleep %ld ms...\n", sleep_time_ms);
    clock_gettime(CLOCK_MONOTONIC, &ts_begin); // getsystemtime();
    usleep(sleep_time_ms * 1000);
    clock_gettime(CLOCK_MONOTONIC, &ts_end); // getsystemtime();
    
    elapsed = ts_end.tv_sec - ts_begin.tv_sec;
    elapsed += (ts_end.tv_nsec - ts_begin.tv_nsec) / 1000000000.0;
    printf("elapsed time = %.3lf ms\n\n", elapsed*1000);
    
    return 0;
}