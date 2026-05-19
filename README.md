# Forshell

A shell written in C from scratch, built as a learning project to understand how shells work under the hood and create mine.

## Features

- Command execution (fork/exec)
- Input/output redirections (`>`, `<`, `>>`)
- Pipes (`|`)
- Environment variable expansion (`$HOME`, `$PATH`, etc.)
- Command history (`hist`)
- Built-in commands: `cd`, `help`, `exit`, `hist`

## Build & Run

```bash
gcc main.c -o forshell
./forshell
```

## Usage

```bash
Forshell> ls -la
Forshell> ls | grep .c
Forshell> echo $HOME
Forshell> cat file.txt > output.txt
Forshell> hist
Forshell> cd ..
Forshell> exit
```

## Project Structure

| File | Role |
|------|------|
| `main.c` | Entry point |
| `forshell.c` | Main loop |
| `parse.c` | Tokenizer, redirections, pipes, env vars |
| `builtin.c` | Built-in commands |
| `launch.c` | fork/exec for normal commands |
| `pipe.c` | fork/exec for pipes |
| `fs_exec.c` | Dispatch builtins vs external commands |
| `fs_read_line.c` | User input reading |
| `history.c` | Command history |
| `signals.c` | SIGINT 

## Roadmap

- [x] Basic shell (fork/exec/wait)
- [x] Redirections
- [x] Pipes
- [x] Environment variables
- [x] History
- [x] Ctrl+C handling
- [x] Improved prompt (current directory)
- [x] Tab autocompletion

## Author

Joris Suarez
