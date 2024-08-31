#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int main() {
  time_t t = time(NULL);
  struct tm *tp = localtime(&t);
  printf("ctime:   %sasctime: %s", ctime(&t), asctime(tp));
  tp = gmtime(&t);
  printf("ctime:   %sasctime: %s", ctime(&t), asctime(tp));
  tp->tm_sec += 3600;
  t = mktime(tp);
  printf("%s\n", ctime(&t));

  char buf[BUFSIZ];
  int r = strftime(buf, BUFSIZ, "%I:%M:%S:%p %d %b %Y", tp);
  if (r != 0) {
    printf("strftime: %s\n", buf);
  }
  struct tm tp2;
  char *tc = strptime(buf, "%I:%M:%S:%p %d %b %Y", &tp2);
  printf("strptime: %s\n", asctime(&tp2));
  return 0;
}