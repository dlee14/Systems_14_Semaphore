#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#define KEY 111

int main(int argc, char const *argv[]) {
  printf("$ %s %s\n", argv[0], argv[1]);
  if (strcmp(argv[1], "-c") == 0) {
    char num_sem = *argv[2];
    int sid = semget(KEY, num_sem, IPC_CREAT | IPC_EXCL);
    if (sid > 0) {
      printf("Created a new semaphore: %d\n", sid);
    } else {
      printf("Error: Semaphore already exists\n");
      // printf("Error: %s\n", strerror(errno));
    }
  }
  if (strcmp(argv[1], "-v") == 0) {
    printf("-v\n");
    // view

  }
  if (strcmp(argv[1], "-r") == 0) {
    printf("-r\n");
    // remove
    // char num_sem = *argv[2];
    // int sid = semget(KEY, num_sem, IPC_CREAT | IPC_EXCL);
    // if (sid < 0) {
    //   sid = semget(KEY, num_sem, IPC_CREAT);
    //   // semctl(sid, )
    // } else {
    //   printf("Error: Semaphore not found\n");
    //   // printf("Error: %s\n", strerror(errno));
    // }
  }
  // execvp(argv[0], argv);
  return 0;
}
