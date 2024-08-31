#include <sys/msg.h>
#include <sys/types.h>
#include <tlpi_hdr.h>

#define MAX_MTEXT 1024

struct mbuf {
  long mtype;            /* Message type */
  char mtext[MAX_MTEXT]; /* Message body */
};

static void usageError(const char *progName, const char *msg) {
  if (msg != NULL)
    fprintf(stderr, "%s", msg);
  fprintf(stderr, "Usage: %s [-n] msqid msg-type [msg-text]\n", progName);
  fprintf(stderr, "    -n       Use IPC_NOWAIT flag\n");
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
  int msqid, flags, msg_len;
  struct mbuf msg;
  int opt;

  flags = 0;
  while ((opt = getopt(argc, argv, "n")) != -1) {
    if (opt == 'n') {
      flags |= IPC_NOWAIT;
    } else {
      usageError(argv[0], NULL);
    }
  }
  if (argc < optind + 2 || argc > optind + 3) {
    usageError(argv[0], "Wrong number of arguments\n");
  }
  msqid = atoi(argv[optind]);
  msg.mtype = atoi(argv[optind + 1]);

  if (argc > optind + 2) {
    msg_len = strlen(argv[optind + 2]) + 1;
    if (msg_len > MAX_MTEXT) {
      cmdLineErr("msg-test too long\n");
    }
    memcpy(msg.mtext, argv[optind + 2], msg_len);
  } else {
    msg_len = 0;
  }

  if (msgsnd(msqid, &msg, msg_len, flags) == -1) {
    errExit("msgsnd");
  }
  exit(EXIT_SUCCESS);
}
