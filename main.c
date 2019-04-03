#include <unistd.h>
#include "client.h"
#include "server.h"
#include "messageQueueing.h"
#include "clientSender.h"

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        run_sender();
    } else {
        run_server();
    }
}

