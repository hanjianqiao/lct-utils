#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

typedef void (*sighandler_t)(int);

void sig_handler(int sigNum){
  printf("get signal %d\n", sigNum);
  if(sigNum == SIGINT){
    exit(0);
  }
}

void *thread_task(void *data){
  while(1){
    pause();
    printf("Signal get\n");
  }
}

int main(int argc, char **argv){
  pthread_t thread;
  if(argc < 2){
    printf("Usage: %s cmd\n", argv[0]);
    return 0;
  }

  if(pthread_create(&thread, NULL, &thread_task, NULL)){
    printf("Error creating thread\n");
  }

  signal(SIGHUP, sig_handler);
  signal(SIGINT, sig_handler);
  signal(SIGQUIT, sig_handler);
  signal(SIGILL, sig_handler);
  signal(SIGABRT, sig_handler);
  signal(SIGFPE, sig_handler);
  signal(SIGKILL, sig_handler);
  signal(SIGSEGV, sig_handler);
  signal(SIGPIPE, sig_handler);
  signal(SIGUSR1, sig_handler);

  switch(atoi(argv[1])){
    case 0:
      raise(SIGUSR1);
    break;
    case 1:
      if(argc < 3){
        printf("Usage: %s pid sig\n", argv[0]);
      }else{
        kill(atoi(argv[1]), atoi(argv[2]));
      }
    break;
    case 2:
      if(argc < 3){
        printf("Usage: %s gpid sig\n", argv[0]);
      }else{
        killpg(atoi(argv[1]), atoi(argv[2]));
      }
    break;
    case 3:
      pthread_kill(thread, SIGUSR1);
    break;
    default:
      printf("Error arg1: %s\n", argv[1]);
  }
  while(1);
}
