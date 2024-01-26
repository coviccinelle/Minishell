
#  🌸🦆🦢 **Minishell** 🐣🐤 - _As Beautiful as a Shell_
by Marie-Ines and Thao
(Let's hope it'll go well, and not too long ^^ )

![til](https://github.com/coviccinelle/Minishell/blob/norme/minishell_b.gif)

## Table of Contents
1. [Common Instructions](#common-instructions)
2. [Mandatory Part - Program name: minishell](#mandatory-part)
   - [Files to Turn In](#files-to-turn-in)
   - [Makefile](#makefile)
   - [Arguments](#arguments)
   - [External Functions](#external-functions)
   - [Libraries](#libraries)
   - [Description](#description)
3. [Mandatory Features](#mandatory-features)
   - [Shell Requirements](#shell-requirements)
   - [Redirection and Pipes](#redirection-and-pipes)
   - [Environment Variables](#environment-variables)
   - [Built-in Commands](#built-in-commands)
4. [Bonus Features](#bonus-features)
   - [Logical Operators](#logical-operators)
   - [Wildcards](#wildcards)

## Common Instructions
- Written in C.
- Norm-compliant with penalties for norm errors.
- Functions should not cause unexpected exits or memory leaks.
- Submission of a Makefile for compilation.
- Makefile must contain rules: `$(NAME)`, `all`, `clean`, `fclean`, and `re`.
- Bonus submission includes a separate `_bonus.{c/h}` file.

## Mandatory Part

### Files to Turn In
- Makefile, *.h, *.c

### Makefile
- `NAME`, `all`, `clean`, `fclean`, `re`

### Arguments
- None specified

### External Functions
- `readline`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`, `printf`, `malloc`, `free`, `write`, `access`, `open`, `read`, `close`, `fork`, `wait`, `waitpid`, `wait3`, `wait4`, `signal`, `sigaction`, `sigemptyset`, `sigaddset`, `kill`, `exit`, `getcwd`, `chdir`, `stat`, `lstat`, `fstat`, `unlink`, `execve`, `dup`, `dup2`, `pipe`, `opendir`, `readdir`, `closedir`, `strerror`, `perror`, `isatty`, `ttyname`, `ttyslot`, `ioctl`, `getenv`, `tcsetattr`, `tcgetattr`, `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`

### Libraries
- Libft authorized

### Description
Write a shell with various features including prompt display, history, executable launching, and redirection capabilities.

## Mandatory Features

### Shell Requirements
- Display a prompt when waiting for a new command.
- Working history.

### Redirection and Pipes
- Redirect input (<).
- Redirect output (>).
- Read input until a line with a specified delimiter (<<).
- Redirect output in append mode (>>).
- Implement pipes (|).

### Environment Variables
- Expand environment variables ($ followed by a sequence of characters).
- Expand `$?` to the exit status of the most recently executed foreground pipeline.

### Built-in Commands
- Implement the following builtins:
  - `echo` with option `-n`.
  - `cd` with only a relative or absolute path.
  - `pwd` with no options.
  - `export` with no options.
  - `unset` with no options.
  - `env` with no options or arguments.
  - `exit` with no options.

## Bonus Features

### Logical Operators
- Implement `&&` and `||` with parentheses for priorities.

### Wildcards
- Wildcards (*) should work for the current working directory.

**Note:** Limit yourself to the subject description. Anything not asked is not required. Reference bash if in doubt.

