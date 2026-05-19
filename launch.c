#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
int fs_launch(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    Redirection r = fs_parse(args);

    if (r.isoutfile != NULL){
      if (r.isappend == 1){
        int fd = open(r.isoutfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        dup2(fd, 1);  // remplace stdout par le fichier
        close(fd);
      }
      else {
        int fd = open(r.isoutfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd, 1);  // remplace stdout par le fichier
        close(fd);
      }
    }
      
    if (r.isinfile != NULL){
      int fd = open(r.isinfile, O_RDONLY);
      dup2(fd, 0);  // remplace stdout par le fichier
      close(fd);
    }
    if (execvp(args[0], args) == -1) {
      perror("fs");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("fs");
  } else {
    // Parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}