
#include "Server.h"
#include <signal.h>

int main(int argc, char** argv){
    sigset_t waitset;
    int      sig;

    Server server(argv[1], argv[2]);
    server.redirectMessages();

    sigemptyset(&waitset);
    sigaddset(&waitset, SIGQUIT);

    sigwait(&waitset, &sig);

    return 0;
}