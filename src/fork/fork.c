#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

static void process_test_static() {
    static int k = 0;
    printf("[PID: %d] k:%d, k_ptr:%p\n", getpid(), ++k, &k);
    return ;
}

int main(int argc, char *argv[])
{
    pid_t pid;

    printf("[PID: %d]Main process Star ....\n", getpid());

    for (int i = 0; i < 2; ++i) {
        pid = fork();
        if (pid > 0) {
            continue;
        } else if (pid == 0) {
            printf("[PID: %d]\n", getpid());
            process_test_static();
        } else {
            return -1;
        }
    }
    getchar();
    return 0;
}

/*
*[PID: 8586]Main process Star ....
*[PID: 8588]
*[PID: 8588] k:1, k_ptr:0x55f605f7a014
*[PID: 8587]
*[PID: 8587] k:1, k_ptr:0x55f605f7a014
*[PID: 8589]
*[PID: 8589] k:2, k_ptr:0x55f605f7a014
*/