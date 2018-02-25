#Single Commands Test Cases
#!/bin/sh

make          #runs make file

ls            #lists directory contents

ls -a         #lists directory contents and hidden files

echo hello    #prints hello

mkdir test    #makes a test directory

cd dir        #changes directory

echo "hello my name is thing.txt" >> thing.txt

rm -rf test   #removes test directory



cat thing.txt
ls -a
rm -f thing.txt
ls -l

exit

echo
make clean