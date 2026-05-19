#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int fs_execute(char **args)
{
  int i;
  int pi = 0;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < fs_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }
  i = 0;
  fs_getenv(args);
  while (args[i] != NULL) {                                                                                                                                                                       
      if (strcmp(args[i], "|") == 0) {
        pi = 1;
      }                                                                                                                                                                          
      i++;                                                                                                                                                                                          
    }
  if (pi != 0) {
    return fs_pipe_launch(args);
  }
  return fs_launch(args);
}
