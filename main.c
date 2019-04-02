#include <unistd.h>
#include "client.h"
#include "server.h"
#include "messageQueueing.h"
#include "clientSender.h"

void initialize(){
    server_start();
    client_start();
}

int main() {
    initialize();
    pid_t pid = fork();

    if (pid == 0) {
        sleep(2);
        run_sender();
    } else {
        run_server();
    }
}

