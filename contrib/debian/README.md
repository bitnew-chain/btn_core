
Debian
====================
This directory contains files used to package btnd/btn-qt
for Debian-based Linux systems. If you compile btnd/btn-qt yourself, there are some useful files here.

## btn: URI support ##


btn-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install btn-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your btn-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitcoin128.png` to `/usr/share/pixmaps`

btn-qt.protocol (KDE)

