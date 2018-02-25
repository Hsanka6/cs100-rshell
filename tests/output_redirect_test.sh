#!/bin/sh
#Output Redirection Commands Test Cases

ls > a.txt
ps > a.txt
echo this is test > a.txt
echo hello world > dup.txt
echo hello > dup.txt | cat < dup.txt    #does not work
wc > a.txt                              #does not work
tr a-z A-Z > a.txt
rm a.txt
rm dup.txt
