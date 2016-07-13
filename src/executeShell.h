#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

void executeShell(char command[]){
    FILE *pp;

    initscr();
    cbreak();
    if((pp = popen(command, "r"))!= 0)
    {
        char buffer[50];
        while(fgets(buffer, sizeof(buffer), pp) !=0)
        {
            addstr(buffer);
        }
    getch();
    }
}
