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
  fprintf(stderr, "Usage: %s [options] msqid [max-bytes]\n", progName);
  fprintf(stderr, "Permitted options are:\n");
  fprintf(stderr, "    -e       Use MSG_NOERROR flag\n");
  fprintf(stderr, "    -t type  Select message of given type\n");
  fprintf(stderr, "    -n       Use IPC_NOWAIT flag\n");
#ifdef MSG_EXCEPT
  fprintf(stderr, "    -x       Use MSG_EXCEPT flag\n");
#endif
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
  int msqid, flags, type;
  ssize_t msg_len;
  size_t max_bytes;
  struct mbuf msg;
  int opt;

  flags = 0;
  while ((opt = getopt(argc, argv, "ent:x")) != -1) {
    switch (opt) {
    case 'e':
      flags |= MSG_NOERROR;
      break;
    case 'n':
      flags |= IPC_NOWAIT;
      break;
    case 't':
      type = atoi(optarg);
      break;
    default:
      usageError(argv[0], NULL);
    }
  }
  if (argc < optind + 1 || argc > optind + 2) {
    usageError(argv[0], "wrong number of argument\n");
  }
  msqid = atoi(argv[optind]);
  max_bytes = (argc > optind + 1) ? atoi(argv[optind + 1]) : MAX_MTEXT;
  msg_len = msgrcv(msqid, &msg, max_bytes, type, flags);
  if (msg_len == -1) {
    errExit("msgrcv");
  }
  printf("received: type=%ld; length=%ld", msg.mtype, (long)msg_len);
  if (msg_len > 0)
    printf("; body=%s", msg.mtext);
  printf("\n");
  exit(EXIT_SUCCESS);
}
