#!/bin/sh
#Precedence Commands Test Cases
(ls || ps) && mkdir testdir && echo A
(ls && rm -r testdir) && echo A
(echo hello world)
(ls && rm -r testdir) && echo B
(echo hello world || ls -a) && echo A
(echo A ; echo B) || (echo C && echo D)     #does not run properly
echo A && (ls -l && ls -a) || echo B
(ps && ls) || (echo A && echo B)            #does not run properly
(echo A) ; (echo B)
(echo A && echo B) ; (echo C && echo D)
(ps ; ls) || (ls)
exit