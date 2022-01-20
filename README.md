# Minishell

## Summary

The objective of this project is for you to create a simple shell. \
Yes, your little bash or zsh. You will learn a lot about processes and file descriptors.

<img src="./readmeFiles/demo.gif" width=100% height=100%/>

## Installation & Usage

### Requirements
The only requirements are:
- GNU make
- GCC
- Readline library \
  `brew install readline`

### Building the program

1. Download/Clone this repo

        git clone https://github.com/vasekva/Nutshell
2. `cd` into the root directory and run `make`

        cd Nutshell
        make

<img src="./readmeFiles/compile.gif" width=100% height=100%/>

### Running the program

After building the source, run `./minishell` from the project root.

## Main Project Instructions

### Mandatory part

- Can only use C
- No memory leaks
- Сheck the correctness of the input commands
- Implement a series of builtins:  `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`
- Manage the errors
- Handle program interruption with signals (Ctrl+C, Ctrl+D)
