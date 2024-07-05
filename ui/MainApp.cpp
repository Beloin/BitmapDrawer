//
// Created by beloin on 03/07/24.
//

#include <ncurses.h>
#include <cstdlib>
#include "MainApp.h"
#include "command.h"

// TODO: Make a way to have only one instance of MainApp
WINDOW *mainw;
WINDOW *gridw;

int termx, termy;
short black_pair = 1;
short white_pair = 2;

bool initializeCurses();

void initializeColors();

void MainApp::initializeUI() {
    if (!initializeCurses()) {
        fprintf(stderr, "could not initialize ncurses");
        exit(-1);
    }
    status = Status::ACTIVE;

    getmaxyx(mainw, termy, termx);
    wmove(mainw, (int) .1 * termy, (int) .1 * termx);
    attron(A_STANDOUT);
    wprintw(mainw, "Welcome to bitmap Project!");
    attroff(A_STANDOUT);
    wrefresh(mainw);
}

void MainApp::closeUI() {
    if (status == Status::ACTIVE)
        endwin();

    status = Status::INACTIVE;
}

void printAllGridWhite(int width, int height) {
    wattron(gridw, COLOR_PAIR(white_pair));
    for (int i = 1; i <= width; ++i) {
        for (int j = 1; j <= height; ++j) {
            wmove(gridw, j, i);
            waddch(gridw, ' ');
        }
    }
    wattroff(gridw, COLOR_PAIR(white_pair));
    wrefresh(gridw);
    wrefresh(mainw);
}

void MainApp::createGrid(int width_, int height_) {
    this->width = width_;
    this->height = height_;
    gridw = newwin(height_ + 2, width_ + 2, 1, 1);
    box(gridw, 0, 0);
    printAllGridWhite(width_, height_);
}

void MainApp::changePos(int x, int y) {
    gridX = x;
    gridY = y;
    wmove(gridw, y + 1, x + 1);
    wrefresh(gridw);

    if (onPosChange_ != nullptr)
        onPosChange_(gridX, gridY);
}

[[noreturn]] void MainApp::loop() {
    while (true) {
        Command command = getCommand();

        switch (command) {
            case ENTER:
                setPixel(currentColor);
                break;
            case SPACE:
                if (onSave_ != nullptr)
                    onSave_();
                break;
            case UP:
                if (gridY > 0) {
                    changePos(gridX, --gridY);
                }
                break;
            case DOWN:
                if (gridY < height - 1) {
                    changePos(gridX, ++gridY);
                }
                break;
            case RIGHT:
                if (gridX < width - 1) {
                    changePos(++gridX, gridY);
                }
                break;
            case LEFT:
                if (gridX > 0) {
                    changePos(--gridX, gridY);
                }
                break;
            case NONE:
                break;
        }
    }
}

void MainApp::setPixel(Color color) const {
    wmove(gridw, gridY + 1, gridX + 1);
    short attr;
    switch (color) {
        case BLACK:
            attr = black_pair;
            break;
        case WHITE:
            attr = white_pair;
            break;
    }
    wattron(gridw, COLOR_PAIR(attr));
    waddch(gridw, ' ');
    wattroff(gridw, COLOR_PAIR(attr));

    if (onSet_ != nullptr)
        onSet_(color, gridX, gridY);
}

void MainApp::setSaveCallback(onSave cb) {
    this->onSave_ = cb;
}

void MainApp::setPosChangeCallback(onPosChange cb) {
    this->onPosChange_ = cb;
}

void MainApp::setOnSetCallback(onSet cb) {
    this->onSet_ = cb;
}

bool initializeCurses() {
    mainw = initscr();
    if (mainw == nullptr) return false;

    cbreak();
    noecho();

    start_color();
    initializeColors();

    return true;
}

void initializeColors() {
    init_pair(white_pair, COLOR_BLACK, COLOR_WHITE);
    init_pair(black_pair, COLOR_WHITE, COLOR_BLACK);
}