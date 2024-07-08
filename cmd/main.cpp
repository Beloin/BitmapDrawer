#include <iostream>
#include <csignal>
#include <thread>

#include "../examples/cpp_symbol.h"
#include "MainApp.h"

typedef void (*sig_handler)(int signal);

void wait_sigint(sig_handler sigh);

int status = 0;

void handle_signal(int signal) {
    printf("Signal %d received.\n", signal);
    status = signal;
}

void uiThread(MainApp *mainApp) {
    mainApp->loop();
}

Bitmap *globBitmap;

void onSetCb(Color color, int x, int y) {
    auto p = colorToPixel(color);
    globBitmap->SetPixel(x, y, p);
}

void onPosCb(int x, int y) {

}

void onSaveCb() {
    BitmapWriter writer = *globBitmap;
    writer.Write("../test.bmp");
}


int main(int argc, char *argv[]) {
    MainApp mainApp;
    mainApp.initializeUI();
    mainApp.createGrid(100, 30);
    mainApp.changePos(0, 0);

    mainApp.setOnSetCallback(onSetCb);
    mainApp.setPosChangeCallback(onPosCb);
    mainApp.setSaveCallback(onSaveCb);

    globBitmap = new Bitmap{100, 30};
    globBitmap->SetAll({0, 0, 0});

    std::thread ui{uiThread, &mainApp};

    wait_sigint(handle_signal);
    if (status != 0)
        return 128 + status;

    delete globBitmap;
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