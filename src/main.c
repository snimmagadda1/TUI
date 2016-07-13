#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <panel.h>

/* This is a basic terminal TUI for the Pulse Appliance */

int main(int argc, char *argv[]){
    WINDOW *my_wins[2];
    PANEL *my_panels[2];
    int row, col;                               /* initialize the maximum row and column sizes */
    initscr();                                  /* initialize the ncurses window and standard screen */
    cbreak();                                   /* read in characters as they are typed */
    noecho();                                   /* do not display the users input on cursor */
    getmaxyx(stdscr, row, col);

    my_wins[0] = newwin(row*.5, col*.25, 1, 1);          /* make a window */
    box(my_wins[0], 0, 0);                      /* put box around the window */

    my_panels[0] = new_panel(my_wins[0]);       /* add to panel for organization */
    update_panels();                            /* write to virtual screen in correct order */
    doupdate();                                 /* update the physical screen with panels */

    getch();
    endwin();




    return 0;
}

