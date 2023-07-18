#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    printf("ping\n");
    int p[2];
    int p1[2];
    pipe(p);
    pipe(p1);
    int pid = fork();
    if (pid == 0) {
        close(p[1]);
        char buf[10];
        read(p[0], buf, 10);
        printf("%d: received %s\n", getpid(), buf);
        close(p[0]);
        close(p1[0]);
        write(p1[1], "ping", 4);
        close(p1[1]);
    } else {
        close(p[0]);
        close(p1[1]);
        write(p[1], "pong", 4);
        close(p[1]);
        char buf1[10];
        read(p1[0], buf1, 10);
        printf("%d: received %s\n", getpid(), buf1);
        close(p1[0]);
    }
    exit(0);
}