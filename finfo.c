/******************************************************************************
 * Filename: finfo.c
 * Description: given a file as a command line argument print information about
 *              the file such as type of file, permissions set on the file,
 *              owner of the file, size of file in bytes, and last time 
 *              modified
 * Author: Jacob Newberry
 * Date: 11/20/2026
 *****************************************************************************/

#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>

 int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        struct stat fileStats;
        int result =stat(argv[1], &fileStats);
        if(result == -1)
        {
            perror("Error");
            exit(1);
        }

        printf("File: %s\n", argv[1]);

        //permissions is an int normally read in octal format
        //There are macros defined for file type and permissions
        //that will be used to parse the st_mode field of the stat struct
        int permissions = fileStats.st_mode;
        //this code is shown in the man page for stat
        switch(permissions & S_IFMT)
        {
            case S_IFBLK:
                printf("File Type: Block Device\n");
                break;
            case S_IFCHR:
                printf("File Type: Character Device\n");
                break;
            case S_IFDIR:
                printf("File Type: Directory\n");
                break;
            case S_IFIFO:
                printf("File Type: FIFO/pipe\n");
                break;
            case S_IFLNK:
                printf("File Type: Symlink\n");
                break;
            case S_IFREG:
                printf("File Type: Regular File\n");
                break;
            case S_IFSOCK:
                printf("File Type: Socket\n");
                break;
            default:
                printf("File Type: Unknown\n");
        }
        int user = permissions & S_IRWXU;
        int group = permissions & S_IRWXG;
        int other = permissions & S_IRWXO;

        //prints permissions in format rwx for user, group, and other
        //read, write, execute, - no permission
        printf("User Permissions: ");
        if((user & S_IRUSR) == S_IRUSR)
        {
            printf("r");
        }
        else
        {
            printf("-");
        }
        if((user & S_IWUSR) == S_IWUSR)
        {
            printf("w");
        }
        else
        {
            printf("-");
        }
        if((user & S_IXUSR) == S_IXUSR)
        {
            printf("x");
        }
        else
        {
            printf("-");
        }  
        printf("\n");      

        printf("Group Permissions: ");
        if((group & S_IRGRP) == S_IRGRP)
        {
            printf("r");
        }
        else
        {
            printf("-");
        }
        if((group & S_IWGRP) == S_IWGRP)
        {
            printf("w");
        }
        else
        {
            printf("-");
        }
        if((group & S_IXGRP) == S_IXGRP)
        {
            printf("x");
        }
        else
        {
            printf("-");
        }
        printf("\n"); 

        printf("Other Permissions: ");
        if((other & S_IROTH) == S_IROTH)
        {
            printf("r");
        }
        else
        {
            printf("-");
        }
        if((other & S_IWOTH) == S_IWOTH)
        {
            printf("w");
        }
        else
        {
            printf("-");
        }
        if((other & S_IXOTH) == S_IXOTH)
        {
            printf("x");
        }
        else
        {
            printf("-");
        }
        printf("\n");

        int owner = fileStats.st_uid;
        int size = fileStats.st_size;

        printf("Owner: %d\n", owner);
        printf("Size: %d bytes\n", size);

        //gives time in seconds since epoch which is Jan 1, 1970
        struct timespec lastModified = fileStats.st_mtim;
        //parse time into current date always rounds down to nearest second
        //time of day is shown in military time
        time_t LastModifiedTime = lastModified.tv_sec;
        struct tm *timeinfo = localtime(&LastModifiedTime);
        printf("Last Modified: %02d/%02d/%04d %02d:%02d:%02d\n", timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    }
    else
    {
        printf("Please enter one file name as a command line argument\n");
    }
}