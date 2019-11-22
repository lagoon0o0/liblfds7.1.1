#!/bin/bash
echo "flag: $1"
echo "on the branch:"
git branch | grep \* | cut -d ' ' -f2 
cd liblfds7.1.1/liblfds711/build/gcc_gnumake/
make clean
make $1
sudo make so_uninstall
sudo make so_install 
cd ../../../../