#!/bin/sh
#Pipe Commands Test Cases

echo hello > dup.txt | tee dup.txt
ls | cat
ls -a | grep src
ls | cat | wc
ls | wc
ps | wc
cat < dup.txt | tr A-Z a-z | wc > a.txt
cat < dup.txt | tee dup.txt
echo hello | wc