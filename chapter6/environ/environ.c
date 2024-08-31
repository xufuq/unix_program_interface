#include <stdio.h>
#include <stdlib.h>

extern char** environ;

int main(int argc, char** argv) {
  for (size_t i = 0; i < argc; ++i) {
    printf("argv[%ld] = %s\n", i, argv[i]);
  }
  size_t i = 0;
  for (char** p = environ; *p != NULL; ++p) {
    printf("environ[%ld]: %s\n", i++, *p);
  }
  char* res = getenv("USER3");
  if (res == NULL) {
    printf("%s\n", "empty");
  } else {
    printf("%s\n", res);
  }
  putenv("USER2=Yang");
  printf("%s\n", getenv("USER2"));
  return 0;
}