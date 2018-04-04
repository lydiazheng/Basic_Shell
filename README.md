# Basic Shell
## Introduction
This is a shell program that can implement some basic commands such as ls, cat, history, and exit. This is a school project for the Operating System course. It was designed to learn basic OS function call in C.

## How to run this program:
1. type 'make'
2. type './testfile'
3. It will show my_shell: CMPT300@my_shell:~$
4. you need to type the command to run this program

## Demo
Features include:
1. internal commands: exit, cd, pwd, history
2. external commands: ls, cat

The output sample:

```weilingz@asb9838nu-b13:~/Desktop/Assignment#1_part2$ make
make: Nothing to be done for `all'.
weilingz@asb9838nu-b13:~/Desktop/Assignment#1_part2$ ./testfile
CMPT300@my_shell:~$ ls
makefile  my_shell.c  my_shell.o  README.txt  sss  testfile  textfile.txt
CMPT300@my_shell:~$ pwd
Directory:  /home/weilingz/Desktop/Assignment#1_part2
CMPT300@my_shell:~$ cd sss
CMPT300@my_shell:~$ pwd
Directory:  /home/weilingz/Desktop/Assignment#1_part2/sss
CMPT300@my_shell:~$ cd ..
CMPT300@my_shell:~$ cat textfile.txt
lydia
lydia
lydia
lydia
lydia
lydia
lydia
lydia
lydia
lydia
CMPT300@my_shell:~$ history

   1 ls
   2 pwd
   3 cd sss
   4 pwd
   5 cd ..
   6 cat textfile.txt
   7 history

CMPT300@my_shell:~$ exit
Wow! my_shell exit!```
