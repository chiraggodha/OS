#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int p[2]; 
    pipe(p);

    int pid = fork();

    if (pid < 0) {
        fprintf(2, "fork failed\n");
        exit(1);
    } 
    else if (pid == 0) {
        // Child process
        char buf[4];
        read(p[0], buf, 4);  
        printf("%d: received ping\n", getpid());
        write(p[1], "pong", 4); 
    } 
    else {
        // Parent process
        write(p[1], "ping", 4); 
        char buf[4];
        read(p[0], buf, 4);    
        printf("%d: received pong\n", getpid());
    }

    exit(0);
}