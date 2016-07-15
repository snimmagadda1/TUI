#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>

void drawBorders( WINDOW *win)
{   
    int x, y, i;
    getmaxyx(win, y, x); 
    mvwprintw(win,0,0,"+");
    mvwprintw(win, y-1,0,"+");
    mvwprintw(win,0,x-1,"+");
    mvwprintw(win,y-1, x-1, "+");

    /* sides */
    
    for(i=1; i<(y-1); i++)
    {
        mvwprintw(win, i, 0, "|");
        mvwprintw(win, i,x-1, "|");
    }
    
    /*top and bottom */
    
    for(i=1; i<(x-1); i++)
    {
        mvwprintw(win,0,i,"-"); 
        mvwprintw(win, y-1,i,"-");
    }
    
}
