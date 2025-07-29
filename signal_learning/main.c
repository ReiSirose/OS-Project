#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //linux lib
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

int main (int argc, char* argv[]) {
    if(mkfifo("myfifo", 0777) == -1){
        if (errno != EEXIST){
            printf("Could not create fifo file \n");
            return 1;
        }
    }

    printf("Openning....\n");
    int fd = open("myfifo", O_WRONLY);
    printf("Opened\n");
    int x = 97;
    if(write(fd, &x, sizeof(x)) == -1){
        return 2;
    }

    printf("Written \n");
    close(fd);
    printf("Written \n");
    unlink("myfifo");

    return 0;
}