#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>

#include "history.c"
#include "builtin.c"
#include "parse.c"
#include "pipe.c"
#include "launch.c"
#include "fs_exec.c"
#include "signals.c"


void fs_loop(void)
{
  char *line;
  char **args;
  int status;
  char cwd[1024];


  signal(SIGINT, handle_sigint); //Traite les signals unix pour le terminal

  do {
    getcwd(cwd, sizeof(cwd));
    char prompt[1100];
    snprintf(prompt, sizeof(prompt), "%s\nForshell> ", cwd);
    line = readline(prompt);
    args = fs_split_line(line);
    status = fs_execute(args);
    fs_history(strdup(line));

    free(line);
    free(args);
  } while (status);
}