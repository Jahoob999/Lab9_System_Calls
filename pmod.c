/******************************************************************************
 * Filename: pmod.c
 * Description: decreases the priority of the current process by 10
 *              waits 1,837,272,638 nano seconds and prints a good bye message
 * Author: Jacob Newberry
 * Date: 11/10/26
 *****************************************************************************/

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #include <unistd.h>

int main(int argc, char* argv[])
{
    //adds 10 to the nice value (higher nice value = lower prio)
    nice(10);

    //timespec used for nanosleep
    struct timespec *time = malloc(sizeof(struct timespec));
    time->tv_sec = 1;
    time->tv_nsec = 837272638;

    //sleeps for time specified in timespec
    nanosleep(time, NULL);
    printf("goodbye\n");

    free(time);

    return 0;
}