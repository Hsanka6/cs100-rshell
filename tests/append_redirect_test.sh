#!/bin/sh
#Append Redirection Commands Test Cases

ls > a.txt
ps >> a.txt
rm a.txt
ps > a.txt
ls >> a.txt
echo hello > dup.txt
echo hi >> dup.txt
cat < dup.txt
wc >> dup.txt
