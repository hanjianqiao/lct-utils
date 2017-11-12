/* unshare.c

  A simple implementation of the unshare(1) command: unshare
  namespaces and execute a command.
*/
#define _GNU_SOURCE
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/* It's new, glibc may not have this */

#ifndef CLONE_NEWCGROUP
    #define CLONE_NEWCGROUP 0x02000000
#endif

/* A simple error-handling function: print an error message based
  on the value in 'errno' and terminate the calling process */

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                       } while (0)

static void
usage(char *pname)
{
   fprintf(stderr, "Usage: %s [options] program [arg...]\n", pname);
   fprintf(stderr, "Options can be:\n");
   fprintf(stderr, "    -i   unshare IPC namespace\n");
   fprintf(stderr, "    -m   unshare mount namespace\n");
   fprintf(stderr, "    -n   unshare network namespace\n");
   fprintf(stderr, "    -p   unshare PID namespace\n");
   fprintf(stderr, "    -u   unshare UTS namespace\n");
   fprintf(stderr, "    -U   unshare user namespace\n");
   fprintf(stderr, "    -C   unshare cgroup namespace\n");
   exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[])
{
   int flags, opt;

   flags = 0;

   while ((opt = getopt(argc, argv, "imnpuUC")) != -1) {
       switch (opt) {
       case 'i': flags |= CLONE_NEWIPC;        break;
       case 'm': flags |= CLONE_NEWNS;         break;
       case 'n': flags |= CLONE_NEWNET;        break;
       case 'p': flags |= CLONE_NEWPID;        break;
       case 'u': flags |= CLONE_NEWUTS;        break;
       case 'U': flags |= CLONE_NEWUSER;       break;
       case 'C': flags |= CLONE_NEWCGROUP;       break;
       default:  usage(argv[0]);
       }
   }

   if (optind >= argc)
       usage(argv[0]);

   if (unshare(flags) == -1)
       errExit("unshare");

   execvp(argv[optind], &argv[optind]);
   errExit("execvp");
}