
Debian
====================
This directory contains files used to package adirondackd/adirondack-qt
for Debian-based Linux systems. If you compile adirondackd/adirondack-qt yourself, there are some useful files here.

## adirondack: URI support ##


adirondack-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install adirondack-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your adirondackqt binary to `/usr/bin`
and the `../../share/pixmaps/adirondack128.png` to `/usr/share/pixmaps`

adirondack-qt.protocol (KDE)

