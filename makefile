CC= g++

CFLAGS = -Wall -Werror -ansi -pedantic

all:
	mkdir -p ./bin
	$(CC) $(CFLAGS) ./src/main.cpp -o ./bin/rshell

main:
	$(CC) $(CFLAGS) ./src/main.cpp


clean:
	rm -rf ./bin








