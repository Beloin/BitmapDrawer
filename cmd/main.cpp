#include <iostream>
#include <csignal>

#include "../examples/cpp_symbol.h"
#include "MainApp.h"

typedef void (*sig_handler)(int signal);

void wait_sigint(sig_handler sigh);

int status = 0;

void handle_signal(int signal) {
    printf("Signal %d received.\n", signal);
    status = signal;
}


int main(int argc, char *argv[]) {
    MainApp mainApp;
    mainApp.initializeUI();
    mainApp.createGrid(100, 30);

    wait_sigint(handle_signal);
    if (status != 0)
        return 128 + status;

    mainApp.closeUI();
    return 0;
}


void wait_sigint(sig_handler sigh) {
    sigset_t set;
    int sig = -1;
    struct sigaction sa{};
    sa.sa_handler = sigh;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigemptyset(&set);
    sigaddset(&set, SIGINT);

    while (sig != SIGINT) {
        sigwait(&set, &sig);

        if (sig != SIGINT)
            printf("press ^C to exit\n");
    }

    printf("\n");
}