#include <unistd.h>
#include <stdio.h>
#include "client.h"
#include "server.h"
#include "messageQueueing.h"
#include "clientCLI.h"

int main(int argc, char ** argv) {
    pid_t pid = fork();

    if (pid == 0) {
        run_sender(stdin);
    }
    else {
        run_server();
    }
}

