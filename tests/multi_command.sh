#!/bin/sh
#Multi Commands Test Cases

echo hello world || ls -a; ps     #Should print "hello world" and PID numbers.
ls -a && mkdir yolo               #Should print out items in directory and create directory yolo
rm -rf yolo ; ls                  #Should remove directory yolo and ls
echo "this is a test" || echo "the first test failed" && ls      #BUG, echo can only print two words
echo clear hello; clear           #prints out "clear hello" and clears the page
ls -q || ps                       
touch test.cpp; echo created test.cpp && rm test.cpp    #Creates, prints and removes test.cpp
ls -a || ls && ls                
cat notexist.cc && echo invalid cat 
cd yolo && exit                   #Change directory to yolo and exit