#include <stdio.h>
#include <unistd.h>

#define MAX_COUNT 200

void ChildProcess(void) {
    for (int i = 1; i <= MAX_COUNT; i++) {
        printf("This line is from child, value = %d\n", i);
    }
}

void ParentProcess(void) {
    for (int i = 1; i <= MAX_COUNT; i++) {
        printf("This line is from parent, value = %d\n", i);
    }
}

int main() {
    int pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        ChildProcess();
    } else {
        ParentProcess();
    }

    return 0;
}
