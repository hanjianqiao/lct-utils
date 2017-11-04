#include  <stdio.h>
#include  <signal.h>
#include  <stdlib.h>
#include <unistd.h>

void INThandler(int);

volatile int should_stop = 0;

int main(void){
    signal(SIGINT, INThandler);
    while (should_stop == 0)
        pause();
    return 0;
}

void  INThandler(int sig)
{
    char  c;

    signal(sig, SIG_IGN);
    printf("OUCH, did you hit Ctrl-C?\n"
        "Do you really want to quit? [y/n] ");
    c = getchar();
    if (c == 'y' || c == 'Y')
        should_stop = 1;
    else
        signal(SIGINT, INThandler);
    getchar(); // Get new line character
}