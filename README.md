# Sea Shell

Sea shell is a shell like program that executes certain commands by doing execvp(), dup2() system calls. 


## Requirements
- need to have boost installed


## Installation

```Installation
$ git clone https://github.com/cs100/rshell-AssnSquad.git

$ cd rshell-AssnSquad

$ make

$ ./bin/rshell
```

## Features
Sea Shell supports all connectors such as;
- ";" = The following command will always be exectued.
- "||" = If the current command fails, the following command will be executed.
- "&&" = If the current command succeeds, the following command will be executed.
- "#" = Everything after "#" will be a comment.

## Bugs
- may have memory leaks
- Some || and && connectors don't work in certain test cases
- Some piping cases don't work


## Usage

This version of Sea Shell supports ```ls``` with forms:
* ```ls``` will display all files and folders
* ```ls -a``` will display all files and folders including hidden folders and files

This version of Sea Shell supports ```echo``` with forms:
* ```echo <string>``` will print out the following string to the shell

This version of Sea Shell supports ```mkdir``` with forms:
* ```mkdir <string>``` will make a directory with input you passed in

This version of Sea Shell supports ```test -e, -d, -f``` with forms:
* ```test -e <path>``` and ```[ -e <path> ]``` will check if path exists
* ```test -d <path>``` and ```[ -d <path> ]``` will checks if directory exists
* ```test -f <path>``` and ```[ -f <path> ]``` will check if file exists

This version of Sea Shell supports input and output redirection with forms:
* ```test -e <path>``` and ```[ -e <path> ]``` will check if path exists
* ```test -d <path>``` and ```[ -d <path> ]``` will checks if directory exists
* ```test -f <path>``` and ```[ -f <path> ]``` will check if file exists

## Execution using Tree Representation
We used a tree to execute multiple commands. The parent nodes are the tokens- ";", "||", "&&", "|" and the left and right children are the commands.
Sea Shell uses inorder traversal to execute the commands.

![Alt text](/SpecialDocs/tree.png?raw=true "Optional Title")

## To Do
- Fix piping 
- Fix some of the precedence cases


## Authors:
* Haasith Sanka - https://github.com/Hsanka6
* Venkat Prathipati - https://github.com/vprat001



## License 
You may use, distribute and copy Kodi under the terms of GNU General
 Public License version 2, which is displayed below.

-------------------------------------------------------------------------

		    GNU GENERAL PUBLIC LICENSE
		       Version 2, June 1991

 Copyright (C) 1989, 1991 Free Software Foundation, Inc.
                       59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 Everyone is permitted to copy and distribute verbatim copies
 of this license document, but changing it is not allowed.






