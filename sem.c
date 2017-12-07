#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#define KEY 111

void create_sem();
void get_value();
int sem_value();
void remove_sem();

int main(int argc, char const *argv[]) {
  if (argv[1] != NULL) {
    if (!strcmp(argv[1], "-c")) {
      create_sem(argc, argv);
    }
    else if (!strcmp(argv[1], "-v")) {
      get_value(argc, argv);
    }
    else if (!strcmp(argv[1], "-r")) {
      remove_sem(argc, argv);
    }
  } else {
    printf("Error: You don't know what you're doing, or you made a mistake. I'm sorry, that was really mean.\n");
  }
  return 0;
}

void create_sem(int argc, char const *argv[]) {
  int sid, val;
  if (argc > 2) {
    sid = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0664);
    val = atoi(argv[2]);

    if (sid > 0) {
      semctl(sid, 0, SETVAL, atoi(argv[2]));
      printf("Creating new semaphore:\n");
      printf("\t[id]: %d\n", sid);
      printf("\t[value]: %d\n", atoi(argv[2]));
    } else {
      sid = semget(KEY, 1, IPC_CREAT);
      printf("Error: Semaphore already exists:\n");
      printf("\t[id]: %d\n", sid);
      printf("\t[value]: %d\n", sem_value(sid));
    }
  } else {
    printf("Error: Value of the semaphore not found in the argument\n");
    printf("\t./<program> -c <value>\n");
  }
}

void get_value(int argc, char const *argv[]) {
  int sid, val;
  sid = semget(KEY, 1, 0664);
  if (sid != -1) {
    printf("\t[id]: %d\n", sid);
    printf("\t[value]: %d\n", sem_value(sid));
  } else {
    printf("Error: No semaphore found\n");
  }
}

int sem_value(int sid) {
  int val = semctl(sid, 0, GETVAL);
  return val;
}

void remove_sem(int argc, char const *argv[]) {
  int sid, val;
  sid = semget(KEY, 1, 0664);
  if (sid != -1) {
    printf("Deleting semaphore:\n");
    printf("\t[id]: %d\n", sid);
    printf("\t[value]: %d\n", sem_value(sid));
    semctl(sid, 0, IPC_RMID);
  } else {
    printf("Error: No semaphore found\n");
  }
}
