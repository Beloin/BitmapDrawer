//
// Created by beloin on 03/07/24.
//

#include <ncurses.h>
#include <cstdlib>
#include "MainApp.h"

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

void MainApp::createGrid(int width, int height) {
    this->width = width;
    this->height = height;
    gridw = newwin(height + 2, width + 2, 1, 1);
    box(gridw, 0, 0);
    printAllGridWhite(width, height);
}

void MainApp::changePos(int x, int y) {
    mvwin(gridw, y, x);
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