#include "csapp.h"

void catch_child(int signo) {
    printf("Child exited!\n"); // this call may reenter printf/puts! BAD!  DEADLOCK!
    /*
    - So the prinf function will try to require a lock, but the lock belong to main function.
    - So inorder to release the lock the main function have to wait for the signal to exits
    -> deadlock
    */
    while (waitpid(-1, NULL, WNOHANG) > 0) continue; // reap all children
}

int main(int argc, char** argv) {
    char buf[MAXLINE];
    int i;
    signal(SIGCHLD, catch_child);
    for (i = 0; i < 1000000; i++) {
	if (fork() == 0) {
	    // in child, exit immediately
	    exit(0);
	}
	// in parent
	sprintf(buf, "Child #%d started\n", i);
	printf("%s", buf);
    }
    return 0;
}
