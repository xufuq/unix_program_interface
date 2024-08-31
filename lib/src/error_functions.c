#include "error_functions.h"

#include <stdarg.h>

#include "ename.c.h"
#include "tlpi_hdr.h"

static void terminate(Boolean useExit3) {
  char *s;

  s = getenv("EF_DUMPCORE");
  if (s != NULL && *s != '\0') {
    abort();
  } else if (useExit3) {
    exit(EXIT_FAILURE);
  } else {
    _exit(EXIT_FAILURE);
  }
}

static void outputError(Boolean useErr, int err, Boolean flushStdout,
                        const char *format, va_list ap) {
#define BUF_SIZE 500
  char buf[BUF_SIZE], userMsg[BUF_SIZE], errText[BUF_SIZE];
  vsnprintf(userMsg, BUF_SIZE, format, ap);  // v的含义是可接受变长参数ap

  if (useErr) {
    snprintf(errText, BUF_SIZE, " [%s %s]",
             (err > 0 && err <= MAX_ENAME) ? ename[err] : "?UNKNOWN?",
             strerror(err));
  } else {
    snprintf(errText, BUF_SIZE, ":");
  }

  snprintf(buf, BUF_SIZE, "ERROR%s %s\n", errText, userMsg);

  if (flushStdout) {
    fflush(stdout);
  }
  fputs(buf, stderr);
  fflush(stderr);
}

void errMsg(const char *format, ...) {
  va_list arg_list;
  int savedErrno;

  savedErrno = errno;
  va_start(arg_list, format);
  outputError(TRUE, errno, TRUE, format, arg_list);
  va_end(arg_list);

  errno = savedErrno;
}

void errExit(const char *format, ...) {
  va_list arg_list;

  va_start(arg_list, format);
  outputError(TRUE, errno, TRUE, format, arg_list);
  va_end(arg_list);

  terminate(TRUE);
}

void err_exit(const char *format, ...) {
  va_list arg_list;

  va_start(arg_list, format);
  outputError(TRUE, errno, FALSE, format, arg_list);
  va_end(arg_list);

  terminate(FALSE);
}

void errExitEN(int errnum, const char *format, ...) {
  va_list arg_list;

  va_start(arg_list, format);
  outputError(TRUE, errnum, TRUE, format, arg_list);
  va_end(arg_list);

  terminate(TRUE);
}

void fatal(const char *format, ...) {
  va_list arg_list;

  va_start(arg_list, format);
  outputError(TRUE, 0, TRUE, format, arg_list);
  va_end(arg_list);

  terminate(TRUE);
}

void usageErr(const char *format, ...) {
  va_list arg_list;
  fflush(stdout);

  fprintf(stderr, "Usage: ");
  va_start(arg_list, format);
  vfprintf(stderr, format, arg_list);
  va_end(arg_list);

  fflush(stderr);
  exit(EXIT_FAILURE);
}

void cmdLineErr(const char *format, ...) {
  va_list arg_list;
  fflush(stdout);

  fprintf(stderr, "Commang-line usage error: ");
  va_start(arg_list, format);
  vfprintf(stderr, format, arg_list);
  va_end(arg_list);

  fflush(stderr);
  exit(EXIT_FAILURE);
}
