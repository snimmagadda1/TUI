#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <panel.h>
#include "executeShell.h"
#include "drawBorders.h"
#include "getNetworkInfo.h"
#include "getSystemDisk.h"
/* This is a basic terminal TUI for the Pulse Appliance */
int row, col;

/* initialization of functions */
void getDimensions(WINDOW *win, int *row, int *col, int *middleRow, int *middleCol);
void displayNetworkWindow(WINDOW *win, char *iface, char *ipaddress, char *gateway, char *netmask, char* dns);
void displaySystemWindow(WINDOW *win);
void displayBottomWindow(WINDOW *win, char totalDisk[255], char availDisk[255]);

int main(){
    
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
    char iface[255], ipaddress[255], gateway[255], netmask[255], dns[255], totalDisk[255], availDisk[255];
    getNetworkInfo(fp, iface, ipaddress, netmask, gateway, dns);     
    fclose(fp);
    getSystemDisk(totalDisk, availDisk);
    
    /* Initialize color pairs that will be used in TUI */
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_GREEN); 
    init_pair(2, COLOR_BLACK, COLOR_WHITE);

    /* Initialize the top left and right windows as well as bottom middle window*/
    my_wins[0] = newwin((row*.65)-5, (col*.5)-5,1,5);
    my_wins[1] = newwin((row*.65)-5, (col*.5)-5,1,middleCol);
    int rowStart = getmaxy(my_wins[0]);                                                     /* For later formatting */
    mvprintw(rowStart+3, (col -strlen("System Information"))/2,"System Information");       /* Print title of Window */
    mvprintw(rowStart+2, (col -strlen("pulse.rlpulse.net"))/2, "pulse.rlpulse.net");
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
    displaySystemWindow(my_wins[0]);
    displayNetworkWindow(my_wins[1], iface, ipaddress, gateway, netmask, dns);
    displayBottomWindow(my_wins[2], totalDisk, availDisk);
    attron(A_REVERSE);
    mvprintw(row-2,5,"[F1 Exit]");
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
    /* function to get the dimensions of a window */
void getDimensions(WINDOW *win, int *row, int *col, int *middleRow, int *middleCol){
   getmaxyx(win, *row, *col);
   *middleRow = *row/2;
   *middleCol= *col/2;
}
    /* function to update the network window with appropriate values */
void displayNetworkWindow(WINDOW *win, char *iface, char *ipaddress, char *gateway, char *netmask, char* dns)
{
    int begy, begx, endy, endx;
    getbegyx(win, begy, begx);
    getmaxyx(win, endy, endx);
    mvwprintw(win,1, (endx-strlen("General Information"))/2, "General Information");
    mvwprintw(win, 3, 1, "Interface:");
    mvwprintw(win, 3, 15, "%s", iface);
    mvwprintw(win, 4, 1, "IP Address:");
    mvwprintw(win, 4, 15, "%s", ipaddress);
    mvwprintw(win, 5, 1, "Netmask:");
    mvwprintw(win, 5, 15, "%s", netmask);
    mvwprintw(win, 6, 1, "Gateway:");
    mvwprintw(win, 6, 15, "%s", gateway);
    mvwprintw(win, 7, 1, "DNS:");
    mvwprintw(win, 7, 15, "%s", dns);
    wrefresh(win);
}
    /* function to update the system window with appropriate values */
void displaySystemWindow(WINDOW *win)
{
    int endy, endx;
    getmaxyx(win, endy, endx);
    mvwprintw(win, 1, (endx-strlen("System Information"))/2, "System Information");
    mvwprintw(win, 3, 1, "Pulse Appliance: v1.0.0-beta");
    wrefresh(win);
}

void displayBottomWindow(WINDOW *win, char totalDisk[255], char availDisk[255])
{
    mvwprintw(win, 1,2,"Disk");
    mvwprintw(win, 1,15,"|");
    mvwprintw(win, 1, 17,"Free:");
    mvwprintw(win, 1, 23,"%s",availDisk);
    mvwprintw(win, 1, 28, "/");
    mvwprintw(win, 1, 30,"%s",totalDisk);

    mvwprintw(win, 2,2, "Swap");
    mvwprintw(win, 2, 15, "|");

    mvwprintw(win, 3, 2, "Memory");
    mvwprintw(win, 3, 15, "|");
    wrefresh(win);
}
