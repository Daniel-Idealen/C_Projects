#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#define CURRENT_DIR "."
#define DISPLAY_HIDDEN 1
#define TRAVERSE_FAILURE -1
#define NOT_DISPLAY_HIDDEN 0

int traverse(const char* path, int is_hidden_display) {
  DIR *dir = opendir(path);
  struct dirent *pd;
  
  if (dir == NULL) {
    fprintf(stderr, "Can't open dir!\n");
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
  
  /* TODO: Rewrite this to switch-case statment */
  if (argc == 2 && (strcmp(argv[1], "-a") == 0))
     status = traverse(CURRENT_DIR, DISPLAY_HIDDEN);
  else if (argc == 2)
    status = traverse(argv[1], NOT_DISPLAY_HIDDEN);
  if (argc == 3 && (strcmp(argv[2], "-a") == 0))	
    status = traverse(argv[1], DISPLAY_HIDDEN);
  else
    status = traverse(CURRENT_DIR, NOT_DISPLAY_HIDDEN);
  
  if (status == TRAVERSE_FAILURE)
    exit(1);
  
  return 0;
}
