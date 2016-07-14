#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <panel.h>
#include <string.h>
#define _GNU_SOURCE
void getNetworkInfo(FILE *fp, char iface[255], char ipaddress[255], char netmask[255], char gateway[255], char dns[255]); 
char *copySecond(char *buffer);
/*
int main()
{
    FILE *fp;
    char iface[255];
    char ipaddress[255];
    char gateway[255];
    char netmask[255];
    char dns[255];
    fp= fopen("/home/snimmagadda/Documents/TUI/lib/interfaces","r");
    getNetworkInfo(fp, iface,ipaddress, netmask, gateway, dns);
    
    fclose(fp);
    return 0;
}
*/

char *copySecond( char *buffer)
{
    strtok(buffer, " ");
    return strtok(NULL, " ");

}

void getNetworkInfo(FILE *fp, char iface[255], char ipaddress[255], char netmask[255], char gateway[255], char dns[255])
{
    bool foundPrimary=false;
    char buffer[255];
    while(fgets(buffer, 255, fp))
    {
        if(strstr(buffer, "primary network interface") != NULL)
        {
            foundPrimary = true;
        }
        if(foundPrimary && (strstr(buffer, "iface") != NULL))
        {
            strcpy(iface, copySecond(buffer));
        }
        if(foundPrimary && (strstr(buffer, "address") != NULL))
        {
            strcpy(ipaddress, copySecond(buffer));
        }
        if(foundPrimary && (strstr(buffer, "netmask") != NULL))
        {
            strcpy(netmask, copySecond(buffer));
        }
        if(foundPrimary && (strstr(buffer, "gateway") != NULL))
        {
            strcpy(gateway, copySecond(buffer));
        }
        if(foundPrimary && (strstr(buffer, "dns-nameserver") != NULL))
        {
            strcpy(dns, copySecond(buffer));
            foundPrimary=false;
        }
    }
}


