#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#define CURRENT_DIR        "."
#define DISPLAY_HIDDEN     1
#define TRAVERSE_FAILURE  -1
#define NOT_DISPLAY_HIDDEN 0

int traverse(const char* path, int is_hidden_display) {
  DIR *dir = opendir(path);
  struct dirent *pd;
  
  if (dir == NULL) {
    fprintf(stderr, "opendir: ");
    perror("dir: ");
    return TRAVERSE_FAILURE;
  }

  while ((pd = readdir(dir)) != NULL) {
    if (pd->d_name[0] == '.' && !is_hidden_display)
      continue;
    
    printf("%s\t", pd->d_name);
  }
  printf("\n");
  
  closedir(dir);
  
  return 0;
}

int main(int argc, char** argv) {
  int status;
  char program_name[256];
  strcpy(program_name, argv[0]);
  
  /* TODO: Rewrite this to switch-case statment */
  switch (argc) {
  case 1:
    status = traverse(CURRENT_DIR, NOT_DISPLAY_HIDDEN);
    break;
  case 2:
    if (strcmp(argv[1], "help") == 0) {
      if (program_name == NULL) { /* if (!program_name) alternative */
	fprintf(stderr, "Program name is NULL\n");
      }
      printf("  Help:                             \
              \n\tUsage: %s filename		\
              \n\t-a display hidden files.		\
	     \n");
    }
    else if (strcmp(argv[1], "-a") == 0) {
      status = traverse(CURRENT_DIR, DISPLAY_HIDDEN);
      break;
    } else if (*argv[1] == '-') {
      fprintf(stderr, "Undefined flag: %s. Use help.\n", argv[1]);
      exit(1);
    }
  }
  
  return 0;
}
