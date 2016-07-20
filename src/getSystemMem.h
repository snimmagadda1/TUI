#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getSystemMem(char totalRAM[255], char availRAM[255], char totalSwap[255], char availSwap[255]);
char *extract(char *buffer);
/*
int main()
{
    char totalRAM[255], totalSwap[255], availRAM[255], availSwap[255];
    getSystemMem(totalRAM,availRAM,totalSwap,availSwap);

    return 0;
}
*/



void getSystemMem(char totalRAM[255],char availRAM[255],char totalSwap[255],char availSwap[255])
{
    FILE *fp;
    char buffer[255];
    fp=fopen("/proc/meminfo","r");
    while(fgets(buffer, 255,fp))
    {
        if(strstr(buffer,"MemTotal") != NULL)
        {
           strcpy(totalRAM,extract(buffer));
          // printf("%s\n", totalRAM);
        }
        if(strstr(buffer,"MemFree") != NULL)
        {
            strcpy(availRAM, extract(buffer));
           // printf("%s\n",availRAM);
        }
        if(strstr(buffer,"SwapTotal") != NULL)
        {
            strcpy(totalSwap, extract(buffer));
            //printf("%s\n", totalSwap);
        }
        if(strstr(buffer,"SwapFree") != NULL)
        {
            strcpy(availSwap, extract(buffer));
           // printf("%s\n",availSwap);
        }
    }
    fclose(fp);
}



/* Function to get second word on line from ouptut of fgets */
char *extract(char *buffer)
{
    strtok(buffer, " ");
    return strtok(NULL, " ");
}

