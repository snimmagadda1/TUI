#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <panel.h>
#include "executeShell.h"
#include "drawBorders.h"
#include "getNetworkInfo.h"
#include "getSystemDisk.h"
#include "getSystemMem.h"


/* This is a basic terminal TUI for the Pulse Appliance */
int row, col;

/* initialization of functions */
void getDimensions(WINDOW *win, int *row, int *col, int *middleRow, int *middleCol);
void displayNetworkWindow(WINDOW *win, char *iface, char *ipaddress, char *gateway, char *netmask, char* dns);
void displaySystemWindow(WINDOW *win);
void displayBottomWindow(WINDOW *win, char totalDisk[255], char availDisk[255], char totalRAM[255], char availRAM[255], char totalSwap[255],char availSwap[255]);
void printAsciiLogo(WINDOW *win, int starty, int startx);
void printPulse(WINDOW *win, int starty, int startx);

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
    char iface[255], ipaddress[255], gateway[255], netmask[255], dns[255], totalDisk[255], availDisk[255], totalRAM[255], totalSwap[255], availRAM[255], availSwap[255];
    getNetworkInfo(fp, iface, ipaddress, netmask, gateway, dns);     
    fclose(fp);
    
    /* Read system Disk info and extrapolate */
    getSystemDisk(totalDisk, availDisk);

    /* Read system Ram info and extrapolate */
    getSystemMem(totalRAM,availRAM,totalSwap,availSwap);
    
    /* Initialize color pairs that will be used in TUI */
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_GREEN); 
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_WHITE);
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
    displayBottomWindow(my_wins[2], totalDisk, availDisk, totalRAM, availRAM, totalSwap, availSwap);
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
    mvwprintw(win,1, (endx-strlen("Network Information"))/2, "Network Information");
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
    printAsciiLogo(win, 5, 1);
    mvwprintw(win, 5, 16,"License: Std.");
    wrefresh(win);
}

void displayBottomWindow(WINDOW *win, char totalDisk[255], char availDisk[255], char totalRAM[255], char availRAM[255], char totalSwap[255], char availSwap[255])
{
    mvwprintw(win, 1,2,"Disk");
    mvwprintw(win, 1,15,"|");
    mvwprintw(win, 1, 17,"Free:");
    mvwprintw(win, 1, 23,"%s",availDisk);
    mvwprintw(win, 1, 29, "/");
    mvwprintw(win, 1, 31,"%s",totalDisk);

    mvwprintw(win, 2, 2, "Swap");
    mvwprintw(win, 2, 15, "|");
    mvwprintw(win, 2, 17, "Free:");
    mvwprintw(win, 2, 23,"%s kB", availSwap);
    mvwprintw(win, 2, 34, "/");
    mvwprintw(win, 2, 36,"%s kB", totalSwap);
    
    mvwprintw(win, 3, 2, "Memory");
    mvwprintw(win, 3, 15, "|");
    mvwprintw(win, 3, 17, "Free:");
    mvwprintw(win, 3, 23, "%s kB", availRAM);
    mvwprintw(win, 3, 34, "/");
    mvwprintw(win, 3, 36, "%s kB", totalRAM);
    printPulse(win, 5,2);
    wrefresh(win);
}


void printAsciiLogo(WINDOW *win, int starty, int startx)
{
    int i;
    // print top horizontal R line
    mvwprintw(win, starty, startx,"*");
    mvwprintw(win, starty, startx+1, " ");
    mvwprintw(win, starty, startx+2, "*");
    mvwprintw(win, starty, startx+3, " ");
    mvwprintw(win, starty, startx+4, "*");
    
    // print the vertial R line  and L vertical line
    mvwprintw(win, starty, startx+7, "*");
    for(i=1; i<8; i++)
    {
        mvwprintw(win, starty +i, startx, "*");
        mvwprintw(win, starty+i, startx+7, "*");
    }

    // print bottom horizontal R line 
    mvwprintw(win, starty + 3, startx+2, "*");
    mvwprintw(win, starty + 3, startx+4, "*");

    // print the other vertical R line
    for(i=1; i<3; i++)
    {
        mvwprintw(win, starty +i, startx+4, "*");
    }

    // print diagonal
    mvwprintw(win, starty+4, startx+1, "*");
    mvwprintw(win, starty+5, startx+2, "*");
    mvwprintw(win, starty+6, startx+3, "*");
    mvwprintw(win, starty+7, startx+4, "*");
    
    // print horizontal l line
    mvwprintw(win, starty+7, startx+7,"*");
    mvwprintw(win, starty+7, startx+8," ");
    mvwprintw(win, starty+7, startx+9,"*");
    mvwprintw(win, starty+7, startx+10," ");
    mvwprintw(win, starty+7, startx+11,"*");
    
}

void printPulse(WINDOW *win, int starty, int startx)
{
    int i;
    /* left horizontal line */
    for(i=0;i<27;i++)
    {
        mvwprintw(win, starty, startx+i,"-");
    }

    /*make up and down*/
    mvwprintw(win, starty-1, startx+27,"/");
    mvwprintw(win, starty-1, startx+28,"\\");
    
}
