/******************************************************************************
 * Filename: pinfo.c
 * Description: takes a process identifier as an argument and prints info
 *              about that process. If no argument is given, it prints info 
 *              about the current process
 * Author: Jacob Newberry
 * Date: 11/9/2026
 *****************************************************************************/

 #define _GNU_SOURCE
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <sched.h>
 #include <unistd.h>
 #include <sys/resource.h>
 #include <signal.h>
 #include <errno.h>

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        pid_t process = atoi(argv[1]);
        //checks if process exists, if not kill returns -1
        int result = kill(process, 0);
        if (result == -1)
        {
            perror("Error");
            exit(1);
        }
        int prio = getpriority(PRIO_PROCESS, process);
        int scheduler = sched_getscheduler(process);
        char sched[20];
        //sched_getscheduler returns an int corresponding to scheduler type
        // scheduler types are constants defined in sched.h so we can compare
        // these constants to the return value to convert to string
        if (scheduler == SCHED_OTHER)
        {
            strcpy(sched, "SCHED_OTHER");
        }
        else if (scheduler == SCHED_BATCH)
        {
            strcpy(sched, "SCHED_BATCH");
        }
        else if (scheduler == SCHED_IDLE)
        {
            strcpy(sched, "SCHED_IDLE");
        }
        else if (scheduler == SCHED_FIFO)
        {
            strcpy(sched, "SCHED_FIFO");
        }
        else if (scheduler == SCHED_RR)
        {
            strcpy(sched, "SCHED_RR");
        }
        printf("Process ID: %d \nPriority: %d \nScheduler: %s\n", process, prio, sched);
    }
    else if (argc > 2)
    {
        printf("Too many arguments, provide only one process identifier\n");
    }
    else
    {
        pid_t process = getpid();
        int prio = getpriority(PRIO_PROCESS, process);
        int scheduler = sched_getscheduler(process);
        char sched[20];
        //sched_getscheduler returns an int corresponding to scheduler type
        // scheduler types are constants defined in sched.h so we can compare
        // these constants to the return value to convert to string
        if (scheduler == SCHED_OTHER)
        {
            strcpy(sched, "SCHED_OTHER");
        }
        else if (scheduler == SCHED_BATCH)
        {
            strcpy(sched, "SCHED_BATCH");
        }
        else if (scheduler == SCHED_IDLE)
        {
            strcpy(sched, "SCHED_IDLE");
        }
        else if (scheduler == SCHED_FIFO)
        {
            strcpy(sched, "SCHED_FIFO");
        }
        else if (scheduler == SCHED_RR)
        {
            strcpy(sched, "SCHED_RR");
        }
        printf("Process ID: %d \nPriority: %d \nScheduler: %s\n", process, prio, sched);
    }

    return 0;
}