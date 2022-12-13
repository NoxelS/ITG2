#include <limits.h>  // enthält PIPE_BUF
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>

using namespace std;

void dad(pid_t pid, int fd[2]) {
    char msg[PIPE_BUF];  // pipe-Puffergroessen variieren
                         // zwischen den Betriebssystem
    sprintf(msg, "Ich bin dein Vater...");
    write(fd[1], msg, sizeof(msg));

    waitpid(pid, NULL, 0);  // Auf Sohnprozess warten

    char msgRet[PIPE_BUF];  // pipe-Puffergroessen variieren
    read(fd[0], msgRet, PIPE_BUF);
    printf("SON->DAD: %s  PID=%5d  fd[]=[%d,%d]\n", msgRet, pid, fd[0], fd[1]);
}

void son(pid_t pid, int fd[2]) {
    char msg[PIPE_BUF];  // pipe-Puffergroessen variieren
    read(fd[0], msg, PIPE_BUF);
    printf("DAD->SON: %s  PID=%5d  fd[]=[%d,%d]\n", msg, pid, fd[0], fd[1]);

    char msgRet[PIPE_BUF];
    sprintf(msgRet, "Ich wusste es!");
    write(fd[1], msgRet, sizeof(msg));

    waitpid(pid, NULL, 0);  // Auf Sohnprozess warten
}

int main() {
    int fd[2];
    pipe(fd);  // fd[0] = Pipe-Input, fd[1] = Pipe-Output
    pid_t pid = fork();
    if (pid > 0)
        dad(pid, fd);
    else
        son(pid, fd);
}
