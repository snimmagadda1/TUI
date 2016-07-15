#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void getSystemDisk( char total[255], char avail[255]);
char *copySecond1(char *buffer);
char *copyThird(char *buffer);
/*
int main()
{
    char total[255], avail[255];
    getSystemDisk(total, avail);
    return 0;
}
*/

void getSystemDisk(char total[255], char avail[255])
{
    FILE *fp;
    bool found=false;
    /* command to be executed */
    char command[]="df -h > lib/hdisk.txt";
    char buffer[255];
    char buffer2[255];
    system(command);
    fp=fopen("/home/snimmagadda/Documents/TUI/lib/disk.txt", "r");
    //fp=fopen("/home/rl/Documents/TUI/lib/disk.txt", "r")
    /* get the line with the total system disk info */
    while(fgets(buffer, 255, fp))
    {

        if((strstr(buffer, "/\n") != NULL) && !found)
        {
            strcpy(buffer2, buffer);
            strcpy(total, copySecond1(buffer));
            strcpy(avail, copyThird(buffer2));
            found = true;
        }
        
    }
    fclose(fp);
}

char *copySecond1(char *buffer)
{
    strtok(buffer, " ");
    return strtok(NULL, " ");
}

char *copyThird (char *buffer)
{
    strtok(buffer, " ");
    strtok(NULL, " ");
    return strtok(NULL, " ");
}
