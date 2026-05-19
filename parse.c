#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FS_TOK_BUFSIZE 64
#define FS_TOK_DELIM " \t\r\n\a"
char **fs_split_line(char *line)
{
  int bufsize = FS_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "fs: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, FS_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += FS_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "fs: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, FS_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}


typedef struct {
  char *isinfile;
  char *isoutfile;
  int isappend;
} Redirection;

typedef struct {                                                                                                                                                                                    
    char **left;   // args avant le |                                                                                                                                                                 
    char **right;  // args après le |                                                                                                                                                                 
  } Pipe;

void remove_args(char **args, int i) {                                                                                                                                                              
    int j = i;                                                                                                                                                                                        
    while (args[j+2] != NULL) {                                                                                                                                                                       
      args[j] = args[j+2];                                                                                                                                                                            
      j++;                                                                                                                                                                                          
    }                                                                                                                                                                                                 
    args[j] = NULL;
    args[j+1] = NULL;
  }                  

Redirection fs_parse(char **args){

  Redirection r;
  r.isinfile = NULL;                                                                                                                                                                                  
  r.isoutfile = NULL;                                                                                                                                                                                 
  r.isappend = 0; 

  for (int i = 0; args[i] != NULL; i++)
  {
    if (strcmp(args[i], "<") == 0)
    {
      r.isinfile = args[i+1];
      r.isoutfile = NULL;                                                                    
      r.isappend = 0;
      remove_args(args, i);
    }

    else if (strcmp(args[i], ">") == 0)
    {
      r.isinfile = NULL;
      r.isoutfile = args[i+1];                                                                    
      r.isappend = 0;
      remove_args(args, i);
    }

    else if (strcmp(args[i], ">>") == 0)
    {
      r.isinfile = NULL;
      r.isoutfile = args[i+1];                                                                    
      r.isappend = 1;
      remove_args(args, i);
    }
  }
  return r;
}

Pipe fs_pipe(char **args){
  
  Pipe p;
  p.left = NULL;
  p.right = NULL;

  for (int i = 0; args[i] != NULL; i++)
  {
    if (strcmp(args[i], "|") == 0)                                                                                                                                                                      
    {                                                                                                                                                                                                   
      int len = 0;
      while (args[len] != NULL) len++;
   
      p.left = malloc((i + 1) * sizeof(char*));  

      for (int j = 0; j < i; j++){
        p.left[j] = args[j];
      }
      p.left[i] = NULL;
        
      p.right = malloc((len - i) * sizeof(char*));
      for (int j = 0; args[i+1+j] != NULL; j++){
        p.right[j] = args[i+1+j]; 
      }
      p.right[len-i-1] = NULL;
    }
  }
  return p;
}

void fs_getenv(char **args) {
    int i = 0;
    while (args[i] != NULL) {                                                                                                                                                                       
      if (args[i][0] == '$') {
        args[i] = getenv(args[i] + 1);
      }                                                                                                                                                                          
      i++;                                                                                                                                                                                          
    }
}