#SHELL
Do you know what a shell is?
It is a mostly text-based program that serves as an interface between you, the user, and the OS kernel, it exposes the services of the operating system to the user.
And this project is about creating a simple version, that is capable of the mandatory functionalities,
executing commands, or in simple words a sh shell knockout.
So the shell works ins in 3 modes:
1. First Interactive mode: This is the mode u are probably most familiar with. The shell program prompts u the command, u enter the command, and the shell tries u execute it.
2. Second no-interactive mode: You promote the commands to the shell not via tty but via another source like regular files, pipes, etc
Ex: echo "ls -al" | ./hsh
3. Third the Script mode: In this mode, the shell program gets called with the file as an argument that contains the commands, The shell program will read every line in there and try to execute it  as always.

Our shell implementation is capable of being used in all of these three modes.

#SHELL COMMAND
A shell command in this project is structured as follows
Terminology:
Command [Shell Command]
          |
[Command Portion] [";"] [Command Portion] [";"] [Command Portion] *
                          |
                  [Sub Command] ["||" or "&&"] [Sub Comand] *
A shell command is constructed of command portions that are separated by semi-colons, and every portion is constructed of 0 or any number of subcommands these are separated by logic operators "||" aka or "&&" aka and.
Ex:
```$ ls``` this is a command that is constructed of 1 portion ```[ls]```, and 1 sub command ```[ls]```.
```$ ls; echo "Hi" || cat``` this command is constructed of 1 portions: ```[ls]``` and ```[echo "Hi" || cat]```, ```[ls]``` portion is constructed of 1 subcommand, ```[echo "Hi" || cat]``` is constructed of 2 subcommands ```[echo "Hi"]``` and 
```[cat]```.
Did u get it?
So first we break down the command passed to the shell following this structure, and we execute the subcommand 1 by 1 following the order and the logical operators.

#SHELL EXECUTING A SUBCOMMAND
There are basically 2 types of command executions of command:
1. First we have build-ins those are the commands that the shell program has the code of how to them like ```exit``` which allows u to exit the shell.
2. Second we have the external programs, The shell will not know how to do the job u ask it to do, but it knows that in your system there is a program that knows, so it calls that program. Ex: want to display the content of a file, You know that ```cat``` can do that, so you enter ```cat file```, the shell will search for a program called ```cat``` and forward the file argument u passed to it if found, ```cat``` does its job, and returns to the shell witch return to u.
Our shell obviously able to execute the two command types, and it supports the following buildings:
- ```exit [exit code]```: Allows u to exit the shell.
- ```env```: Prints the envirement varibales of the shell proccess.
- ```setenv/unsetund [key[=value]]```: Allows u to alter the shell env vars.
- ```alias [key[='value']]```: Allows u to declare an alias for the current shell session
- ```cd```: allows u to change the current working directory

#COMPILATION
```./compile.s```
