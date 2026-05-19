#include <string.h>
#include <stdlib.h>
#include <stdio.h>
char *history[1000];
int count = 0;
void fs_history(char *line){
    history[count] = line;
    count++;
}