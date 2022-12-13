#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>
#define FIFO "/tmp/fifo_01"

void startServer() {
    // Wir erzeugen ein FIFO (Dateiname ist natürlich beliebig), falls es
    // nicht schon vorher z.B.  in der Shell oder einem anderen Prozess
    // erzeugt wurde.  Die ~umask (hier: 0) wird mit dem mode-Parameter von
    // mkfifo (hier: 0666) ver-OR-t, um die Zugriffsrechte der named pipe
    // festzulegen (vgl.  umask und mkfifo als Shell-Befehle).
    umask(0);
    mkfifo(FIFO, 0666);
    bool cont = true;
    char ch;
    while (cont) {
        int fd = open(FIFO, O_RDONLY);
        while (read(fd, &ch, 1)) {
            switch (ch) {
                case 'a':
                    printf("a gelesen...\n");
                    break;
                case 'q':
                    printf("Tschüss...\n");
                    cont = false;
                    break;
                default:
                    printf("%c\n", ch);
                    ;
            }
        }
        close(fd);
    }
    remove(FIFO);
}

void startClient() {
    bool cont = true;
    char ch;
    while (cont) {
        int fd = open(FIFO, O_WRONLY);
        std::cin >> ch;
        write(fd, &ch, 1);
        if (ch == 'q') cont = false;
        close(fd);
    }
}

int main() {
    if (fork()) {
        startServer();
    } else {
        startClient();
    }
}
