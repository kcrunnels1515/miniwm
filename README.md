miniwm - dynamic window manager
============================
miniwm is a patched dwm for my laptop and small installs where i need a gui.


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

