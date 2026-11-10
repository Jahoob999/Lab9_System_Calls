/*****************************************************************************
* Filename: info.c
* Description: runs a series of system calls and prints the results
* Author: Jacob Newberry
* Date 10/29/2026
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>


int main(int argc, char* argv[])
{
    struct timespec time;
    //gets time since jan 1, 1970 in seconds and nanoseconds
    clock_gettime(CLOCK_REALTIME, &time);
    //uses localtime to convert the time in seconds to a tm struct which has
    //current seconds minutes and hours of day in correct timezone
    time_t current_time = time.tv_sec;
    struct tm *local_time = localtime(&current_time);
    int timeofday_seconds = local_time->tm_hour * 3600 + local_time->tm_min * 60 + local_time->tm_sec;
    //since ns is always in range 0-999999999 whis is 0.99 seconds just add
    //current time of day in seconds to nanoseconds returned from gettime
    long time_in_nanoseconds = (long)(timeofday_seconds * 1E9) + time.tv_nsec;
    printf("Current time in nanoseconds: %ld\n", time_in_nanoseconds);

    //struct provides network name, os name, os release and version
    //and machine hardware type
    struct utsname sysinfo;
    uname(&sysinfo);
    printf("Network name: %s\n", sysinfo.nodename);
    printf("OS name: %s\n", sysinfo.sysname);
    printf("OS release: %s\n", sysinfo.release);
    printf("OS version: %s\n", sysinfo.version);
    printf("Machine hardware type: %s\n", sysinfo.machine);

    //number of cpus on system
    int cpus = get_nprocs();
    printf("Number of CPUs: %d\n", cpus);

    //find amount of total memory and free memory in bytes
    long page_size = sysconf(_SC_PAGESIZE);
    printf("Page size: %ld bytes\n", page_size);
    //these return the amount of pages in memory so multiply by page size
    //to get the amount of memory in bytes
    long totalmem = sysconf(_SC_PHYS_PAGES);
    long freemem = sysconf(_SC_AVPHYS_PAGES);
    printf("Total memory: %ld bytes\n", totalmem * page_size);
    printf("Free memory: %ld bytes\n", freemem * page_size);

    return 0;
}