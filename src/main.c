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
void displaySystemWindow(WINDOW *win);


int main(int argc, char *argv[]){
    WINDOW *my_wins[3];
    PANEL *my_panels[3];
    int middleRow, middleCol,ch;                /* initialize the middle row and column locations for later use */
    initscr();                                  /* initialize the ncurses window and standard screen */
    cbreak();                                   /* read in characters as they are typed */
    noecho();                                   /* do not display the users input on cursor */
    keypad(stdscr, TRUE);                       /* enable keypad input */
    getDimensions(stdscr, &row, &col, &middleRow, &middleCol); 
    
    /* read network information file and extrapolate useful information */
    FILE *fp;
    fp = fopen("/home/snimmagadda/Documents/TUI/lib/interfaces","r");
    //fp = fopen("/etc/network/interfaces","r");
    char iface[255], ipaddress[255], gateway[255], netmask[255], dns[255];
    getNetworkInfo(fp, iface, ipaddress, netmask, gateway, dns);     
    fclose(fp);
    
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
    
    /* Add color to window backgrounds */
    wbkgd(my_wins[0], COLOR_PAIR(1));
    wbkgd(my_wins[1], COLOR_PAIR(2));

    /* Display information in Network and System Winsows */
    displayNetworkWindow(my_wins[1], iface, ipaddress, gateway, netmask, dns);
    displaySystemWindow(my_wins[0]);
    attron(A_REVERSE);
    mvprintw(row-2,5,"Press F1 to exit");
    attroff(A_REVERSE);
    update_panels();
    doupdate();
    
    /* F1 is exite from TUI */
    while((ch = getch()) != KEY_F(1))
    {
    }
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
    int begy, begx, endy, endx;
    getbegyx(win, begy, begx);
    getmaxyx(win, endy, endx);
    mvwprintw(win,1, (endx-strlen("Network Information"))/2, "Network Information");
    mvwprintw(win, 3, 0, "Interface:");
    wrefresh(win);
}

void displaySystemWindow(WINDOW *win)
{
    int endy, endx;
    getmaxyx(win, endy, endx);
    mvwprintw(win, 1, (endx-strlen("System Information"))/2, "System Information");
}


