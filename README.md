# Linux Homeworks

## Installing C/GCC Compiler
Following are the steps to download and install the MinGW GCC Compiler
1. Open a command line terminal and install C compiler by installation of the development package build-essential:
```
$ sudo apt update
$ sudo apt install build-essential
```

2. Check C compiler version to verify a successful installation:
```
$ gcc --version
```

## How to Run a C Program
In your Terminal, enter the following command to make an executable version of the program
Syntax:
```
$ gcc [programName].c -o programName
```
Example:
```
$ gcc sampleProgram.c -o sampleProgram
```
Make sure your program is located in your Home folder. Otherwise, you will need to specify appropriate paths in this command.

### Run the program
The final step is to run the compiled C program. Use the following syntax to do so:
```
$ ./programName
```

Example:
```
$ ./sampleProgram
```
