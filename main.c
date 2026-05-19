#include <stdlib.h>
#include "forshell.c"
int main(int argc, char **argv)
{
  // Load config files, if any.

  // Run command loop.
  fs_loop();

  // Perform any shutdown/cleanup.

  return EXIT_SUCCESS;
}