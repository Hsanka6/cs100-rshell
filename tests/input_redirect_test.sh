#!/bin/sh
#Input Redirection Commands Test Cases

cat < dup.txt
wc < a.txt
cat < o.txt | tr A-Z a-z
grep 1 < a.txt                  #does not work
echo hello > dup.txt
cat < dup.txt                   #should print "hello" 
echo Hey >> dup.txt
cat < dup.txt                   #should print "hello" and "Hey"