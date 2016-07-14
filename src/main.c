#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <panel.h>
#include "executeShell.h"
#include "drawBorders.h"
#include "getNetworkInfo.h"

/* This is a basic terminal TUI for the Pulse Appliance */
int row, col;

/* initialization of functions */
void getDimensions(WINDOW *win, int *row, int *col, int *middleRow, int *middleCol);
void displayNetworkWindow(WINDOW *win, char *iface, char *ipaddress, char *gateway, char *netmask, char* dns);



int main(int argc, char *argv[]){
    WINDOW *my_wins[3];
    PANEL *my_panels[3];
    int middleRow, middleCol;                   /* initialize the middle row and column locations for later use */
    initscr();                                  /* initialize the ncurses window and standard screen */
    cbreak();                                   /* read in characters as they are typed */
    noecho();                                   /* do not display the users input on cursor */
    getDimensions(stdscr, &row, &col, &middleRow, &middleCol); 
   
    FILE *fp;
    fp = fopen("/home/snimmagadda/Documents/TUI/lib/interfaces","r");
    char iface[255], ipaddress[255], gateway[255], netmask[255], dns[255];
    getNetworkInfo(fp, iface, ipaddress, netmask, gateway, dns);     

    /* Initialize color pairs that will be used in TUI */
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);

    /* Initialize the top left and right windows as well as bottom middle window*/
    my_wins[0] = newwin((row*.65)-5, (col*.5)-5,1,5);
    my_wins[1] = newwin((row*.65)-5, (col*.5)-5,1,middleCol);
    int rowStart = getmaxy(my_wins[0]);
    rowStart+=4;
    my_wins[2] = newwin((row-rowStart)-3, col-10,rowStart, 5);
    my_panels[0] = new_panel(my_wins[0]);
    my_panels[1] = new_panel(my_wins[1]);
    my_panels[2] = new_panel(my_wins[2]);
    drawBorders(my_wins[2]);
    mvwprintw(my_wins[0], 0,0, "%s", ipaddress);
    mvwprintw(my_wins[0], 1,0,"%s", iface);
    mvwprintw(my_wins[0], 2, 0,"%s", netmask);
    mvwprintw(my_wins[0], 3, 0, "%s", gateway);
    mvwprintw(my_wins[0], 4, 0, "%s", dns);
    /* Add color to window backgrounds */
    wbkgd(my_wins[0], COLOR_PAIR(1));
    wbkgd(my_wins[1], COLOR_PAIR(2));
    
    update_panels();
    doupdate();

    fclose(fp);
    getch();
    endwin();
    return 0;
}

void getDimensions(WINDOW *win, int *row, int *col, int *middleRow, int *middleCol){
   getmaxyx(win, *row, *col);
   *middleRow = *row/2;
   *middleCol= *col/2;
}

void displayNetworkWindow(WINDOW *win, char *iface, char *ipaddress, char *gateway, char *netmask, char* dns)
{

}


