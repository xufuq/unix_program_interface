#include "tlpi_hdr.h"
#include <ctype.h>
#include <fcntl.h>
#include <signal.h>
#include <termio.h>

static volatile sig_atomic_t got_sigio = 0;

static void sigio_handler(int sig) { got_sigio = 1; }

int main(int argc, char *argv[]) {
  int flags, j, cnt;
  //  struct termios
  return 0;
}