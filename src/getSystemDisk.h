#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void getSystemDisk( char total[255], char avail[255]);
char *copySecond1(char *buffer);
char *copyFourth(char *buffer);
/*
int main()
{
    char total[255], avail[255];
    getSystemDisk(total, avail);
    printf("%s %s", total, avail);
    return 0;
}
*/

void getSystemDisk(char total[255], char avail[255])
{
    FILE *fp=popen("df -h", "r");
    bool found=false;
    /* command to be executed */
    char buffer[255];
    char buffer2[255];
    //fp=fopen("/home/rl/Documents/TUI/disk.txt", "r");
    /* get the line with the total system disk info */
    while(fgets(buffer, 255, fp))
    {

        if((strstr(buffer, "/\n") != NULL) && !found)
        {
            strcpy(buffer2, buffer);
            strcpy(total, copySecond1(buffer));
            strcpy(avail, copyFourth(buffer2));
            found = true;
        }
        
    }
    pclose(fp);
}

char *copySecond1(char *buffer)
{
    strtok(buffer, " ");
    return strtok(NULL, " ");
}

char *copyFourth (char *buffer)
{
    strtok(buffer, " ");
    strtok(NULL, " ");
    strtok(NULL," ");
    return strtok(NULL, " ");
}
