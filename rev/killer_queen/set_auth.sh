#!/bin/sh
make
chown root:root ./killer_queen flag1.txt 
chmod 4755 ./killer_queen
chmod 600 ./flag1.txt

if [ -d problem ] ; then
    cp -t problem ./killer_queen ./flag1.txt
else 
    mkdir ./problem
    cp -t problem ./killer_queen ./flag1.txt
fi