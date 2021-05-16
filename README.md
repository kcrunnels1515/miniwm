miniwm - dynamic window manager
============================
miniwm is an extremely fast, small, and dynamic window manager for X.


Requirements
------------
In order to build miniwm you need the Xlib header files.


Installation
------------
Edit config.mk to match your local setup (miniwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install miniwm (if
necessary as root):

    make clean install


Running miniwm
-----------
Add the following line to your .xinitrc to start miniwm using startx:

    exec miniwm

In order to connect miniwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec miniwm

(This will start miniwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec miniwm


Configuration
-------------
The configuration of miniwm is done by creating a custom config.h
and (re)compiling the source code.
