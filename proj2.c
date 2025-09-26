#include <stdio.h>
#include <unistd.h>

#define MAX_COUNT 200

void ChildProcess(void) {
    printf("Child process started: PID = %d, PPID = %d\n", getpid(), getppid());
    
    for (int i = 1; i <= MAX_COUNT; i++) {
        printf("This line is from child, value = %d\n", i);
        if (i % 50 == 0) {
            sleep(1); // Задержка каждые 50 итераций
        }
    }
    
    // Заменяем образ процесса на ls -l
    printf("Child process executing ls -l...\n");
    execlp("ls", "ls", "-l", NULL);
    
    // Этот код выполнится только если execlp fails
    perror("execlp failed");
}

void ParentProcess(void) {
    printf("Parent process started: PID = %d, PPID = %d\n", getpid(), getppid());
    
    for (int i = 1; i <= MAX_COUNT; i++) {
        printf("This line is from parent, value = %d\n", i);
        if (i % 30 == 0) {
            sleep(2); // Задержка каждые 30 итераций
        }
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
