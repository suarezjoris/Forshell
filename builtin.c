#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
/*
  Function Declarations for builtin shell commands:
 */
int fsd(char **args);
int fsh(char **args);
int fs_exit(char **args);
int fs_history_builtin(char **args);

/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
  "cd",
  "help",
  "exit",
  "hist"
};

int (*builtin_func[]) (char **) = {
  &fsd,
  &fsh,
  &fs_exit,
  &fs_history_builtin
};

int fs_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

/*
  Builtin function implementations.
*/
int fsd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "fs: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("fs");
    }
  }
  return 1;
}

int fsh(char **args)
{
  int i;
  printf("Joris Suarez Forshell\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < fs_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

int fs_history_builtin(char **args)
{
  int i = 0;
  while (history[i] != NULL){
    printf("%s\n", history[i]);
    i++;
  }
  return 1;
}


int fs_exit(char **args)
{
  return 0;
}
