# TUI
ncurses basic login TUI - This will display basic system and network information

In order to run:
    1). Script runTUI must be executable and placed in accessible directory - change filepath to path to executable 
    2). Edit the exec line on each tty#.conf (generally tty1.conf - tty6.conf to be:
        exec /sbin/getty -l /path/to/runTUI --skip-login -8 -38400 tty#
    
