#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <vector>

#define LOCK -1
#define UNLOCK 1
#define PERM 0666    // gewünschte Zugriffsrechte
#define KEY 123458L  // bel. 'magic key' zur Identifikation des Semaphores

int sema_init() {
    int sid = semget(KEY, 0, IPC_PRIVATE);  // teste ob Semaphor existiert
    if (sid < 0) {
        umask(0);
        sid = semget(KEY, 1, IPC_CREAT | IPC_EXCL | PERM);  // erzeuge Semaphor
        semctl(sid, 0, SETVAL, (int)1);                     // setze auf 1
        printf("(angelegt) ");
    }
    printf("Semaphor-ID : %d\n", sid);
    return sid;
}

void sema_operate(int sid, int op) {
    static struct sembuf myBuffer;
    myBuffer.sem_op = op;         // 1 = Ressource frei, -1 = Ressource belegt
    myBuffer.sem_flg = SEM_UNDO;  // SEM_NOWAIT = nonblocking mit Fehler
                                  // SEM_UNDO = Rücksetzen bei Prozessabbruch
    semop(sid, &myBuffer, 1);     // schreibe neuen sembuf auf Semaphor
}

int main() {
    int semid = sema_init();
    pid_t pid0 = getpid();

    pid_t pids[8];
    for (int i = 0; i < 8; i++) {
        pid_t tmp;
        if (!(tmp = fork())) {
            pids[i] = tmp;
            pid0 = tmp;
            std::cout << "PID: " << tmp << " - " << i << std::endl;
            break;
        }
    }

    printf("PID %d: wartet...\n", pid0);
    sema_operate(semid, LOCK);
    printf("PID %d: arbeitet...\n", pid0);
    sleep(2);
    printf("PID %d: endet.\n", pid0);
    sema_operate(semid, UNLOCK);
    // sleep(5);
    // semctl(semid, 0, IPC_RMID, 0);
}
