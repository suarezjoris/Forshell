#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
int fs_pipe_launch(char **args)
{
  pid_t pid, pidpi, wpid, wpidpi;
  int status;
  Pipe p = fs_pipe(args);
  int pipefd[2];                                                                                                                                                                                      
  pipe(pipefd);
  pid = fork();
  
  if (pid == 0) {
    // Child process

    if (p.left != NULL){
        dup2(pipefd[1], 1);    // ls écrit dans le pipe                                                                                                                                                     
        close(pipefd[0]);                                                                                                                                                                                   
        close(pipefd[1]);                                                                                                                                                                                   
        execvp(p.left[0], p.left);
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
    pidpi = fork();
  }

  if (pidpi == 0) {
    // Child process

    if (p.right != NULL){
        dup2(pipefd[0], 0);    // grep lit depuis le pipe                                                                                                                                                   
        close(pipefd[0]);                                                                                                                                                                                   
        close(pipefd[1]);
        execvp(p.right[0], p.right);
    }
    exit(EXIT_FAILURE);
  } else if (pidpi < 0) {
    // Error forking
    perror("fs");
  } else {
    // Parent process
    do {
        wpid = waitpid(pidpi, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

