#!/bin/sh
#Test Commands Test Cases
test -e a.h && echo a.h exists  
[ -e a.h ] && echo a.h exists
test -d a.h || echo directory a.h 
[ -f a.h ] && echo file exists
test -f a.h
[ -f a.h ] && ls
ls -a && test -f a.h
ls -a && [ -f a.h ]
echo hey || [ -f a.h ]
echo hello || test -f a.h 