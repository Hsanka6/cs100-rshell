#!/bin/sh
#Exit Commands Test Cases

make            #runs make file

ls && exit      #runs ls with exit command


ls || exit     

ls ; exit


ls -a
exit

echo Apple && exit  #exits after executing echo apple

rm -rf yolo || exit #removes yolo directory or exits

echo okay
exit
make clean