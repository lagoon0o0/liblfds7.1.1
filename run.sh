#!/bin/bash
echo "branch $1 flag: $2"
git checkout $1
git pull
echo "on the branch:"
git branch | grep \* | cut -d ' ' -f2 
cd liblfds7.1.1/liblfds711/build/gcc_gnumake/
make clean
make $2
sudo make so_uninstall
sudo make so_install 
cd ../../../../
git checkout bash