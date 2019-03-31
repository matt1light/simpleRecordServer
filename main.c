#include <unistd.h>
#include "client.h"
#include "server.h"

int main() {
    pid_t pid = fork();

    if(pid == 0){
        sleep(2);
        run_client();
    }
    else{
        run_server();
    }
}