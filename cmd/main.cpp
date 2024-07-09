#include <iostream>
#include <csignal>
#include <thread>

#include "../examples/cpp_symbol.h"
#include "MainApp.h"
#include "debug/debug_print.h"

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
    int newY = globBitmap->getHeight() - 1 - y;
    Debug::dprint("Received x:%d and y:%d. Converted to x:%d and y:%d\n", x, y, x, newY);
    auto p = colorToPixel(color);
    globBitmap->SetPixel(x, newY, p);
}

void onPosCb(int x, int y) {

}

void onSaveCb() {
    BitmapWriter writer = *globBitmap;
    const char *fileTest = "../test.bmp";
    writer.Write(fileTest);
    Debug::dprint("Saving to %s\n", fileTest);
}


int main(int argc, char *argv[]) {
    Debug::start();
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
    Debug::stop();
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