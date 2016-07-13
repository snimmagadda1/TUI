#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <panel.h>
#include "executeShell.h"


/* This is a basic terminal TUI for the Pulse Appliance */
int row, col;

/* initialization of functions */
void getDimensions(WINDOW *win, int *row, int *col, int *middleRow, int *middleCol);




int main(int argc, char *argv[]){
    WINDOW *my_wins[3];
    PANEL *my_panels[3];
    int middleRow, middleCol;                   /* initialize the middle row and column locations for later use */
    initscr();                                  /* initialize the ncurses window and standard screen */
    cbreak();                                   /* read in characters as they are typed */
    noecho();                                   /* do not display the users input on cursor */
    getDimensions(stdscr, &row, &col, &middleRow, &middleCol); 
    
    /* Initialize color pairs that will be used in TUI */
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);

    my_wins[0] = newwin((row*.5)-5, (col*.5)-5,0,5);
    my_wins[1] = newwin((row*.5)-5, (col*.5)-5,0,middleCol);
    box(my_wins[0],0,0);
    box(my_wins[1],0,0);
    wbkgd(my_wins[0], COLOR_PAIR(1));
    wbkgd(my_wins[1], COLOR_PAIR(2));
    my_panels[0]=new_panel(my_wins[0]);
    my_panels[1]=new_panel(my_wins[1]);
    
    

    update_panels();
    doupdate();
  
    
    getch();
    endwin();

    return 0;
}

void getDimensions(WINDOW *win, int *row, int *col, int *middleRow, int *middleCol){
   getmaxyx(win, *row, *col);
   *middleRow = *row/2;
   *middleCol= *col/2;

}


