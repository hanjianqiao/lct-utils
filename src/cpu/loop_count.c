#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int forker(int nprocesses)
{
    pid_t pid;

    if(nprocesses > 0)
    {
        if ((pid = fork()) < 0)
        {
            perror("fork");
        }
        else if (pid == 0)
        {
            //Child stuff here
            //printf("Child %d end\n", nprocesses);
            //
        }
        else if(pid > 0)
        {
            //parent
            forker(nprocesses - 1);
            //
        }
    }
    return nprocesses;

}


int main(int argc, char **argv){
	int count = 100000000;
	int loop = 0;
    int nchild = 5;
    if(argc > 1){
        nchild = atoi(argv[1]);
    }
    forker(nchild);
    int id = getpid();
	while(1){
		for(int i = 0; i < count; i++){
			// do nothing
		}
		printf("id %d loop: %d\n", id, loop++);
	}
	return 0;
}
