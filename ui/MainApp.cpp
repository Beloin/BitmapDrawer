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
WINDOW *colorPickerw; // TODO: Create color picker

int termx, termy;
short black_pair = 1;
short white_pair = 2;
short red_pair = 3;
short blue_pair = 4;
short green_pair = 5;
short yellow_pair = 6;

constexpr int pickerRows = 2;
constexpr int pickerCols = 3;

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

void printAllGridBlack(int width, int height) {
    wattron(gridw, COLOR_PAIR(black_pair));
    for (int i = 1; i <= width; ++i) {
        for (int j = 1; j <= height; ++j) {
            wmove(gridw, j, i);
            waddch(gridw, ' ');
        }
    }
    wattroff(gridw, COLOR_PAIR(black_pair));
    wrefresh(mainw);
    wrefresh(gridw);
}

void MainApp::createGrid(int width_, int height_) {
    this->width = width_;
    this->height = height_;
    gridw = newwin(height_ + 2, width_ + 2, 1, 1);
    box(gridw, 0, 0);
    printAllGridBlack(width_, height_);

    wmove(mainw, height_ + 3, 1);
    attron(A_STANDOUT);
    wprintw(mainw, "<S> to Save; vim <keys> to move; <Enter> to toggle color");
}

void MainApp::changeGridPos(int x, int y) {
    gridX = x;
    gridY = y;
    wmove(gridw, y + 1, x + 1);
    wrefresh(gridw);

    if (onPosChange_ != nullptr)
        onPosChange_(gridX, gridY);
}

void MainApp::changePickerPos(int x, int y) {
    pickerX = x;
    pickerY = y;
    wmove(colorPickerw, y + 1, x + 1);
    wrefresh(colorPickerw);
}

[[noreturn]] void MainApp::loop() {
    while (true) {
        Command command = getCommand();

        switch (command) {
            case ENTER:
                if (currentCaretPlace == PICKER) {
                    changeColor();
                    changeCaret();
                    break;
                }

                setPixel(currentColor);
                break;
            case SPACE:
                if (onSave_ != nullptr)
                    onSave_();
                break;
            case UP:
                if (currentCaretPlace == PICKER) {
                    if (pickerY > 0) {
                        changePickerPos(pickerX, --pickerY);
                    }
                    break;
                }

                if (gridY > 0) {
                    changeGridPos(gridX, --gridY);
                }
                break;
            case DOWN:
                if (currentCaretPlace == PICKER) {
                    if (pickerY < pickerRows - 1) {
                        changePickerPos(pickerX, ++pickerY);
                    }
                    break;
                }

                if (gridY < height - 1) {
                    changeGridPos(gridX, ++gridY);
                }
                break;
            case RIGHT:
                if (currentCaretPlace == PICKER) {
                    if (pickerX < pickerCols - 1) {
                        changePickerPos(++pickerX, pickerY);
                    }
                    break;
                }

                if (gridX < width - 1) {
                    changeGridPos(++gridX, gridY);
                }
                break;
            case LEFT:
                if (currentCaretPlace == PICKER) {
                    if (pickerX > 0) {
                        changePickerPos(--pickerX, pickerY);
                    }
                    break;
                }

                if (gridX > 0) {
                    changeGridPos(--gridX, gridY);
                }
                break;
            case SAVE:
                if (onSave_ != nullptr)
                    onSave_();
                break;
            case CHANGE_CARET:
                changeCaret();
                break;
            case NONE:
                break;
        }
    }
}

void MainApp::changeCaret() {
    if (currentCaretPlace == GRID) {
        currentCaretPlace = PICKER;
        wmove(colorPickerw, pickerY + 1, pickerX + 1);
        wrefresh(colorPickerw);
//        wrefresh(mainw);
    } else {
        currentCaretPlace = GRID;
        wmove(gridw, gridY + 1, gridX + 1);
        wrefresh(gridw);
//        wrefresh(mainw);
    }
}

void MainApp::setPixel(Color color) const {
    wmove(gridw, gridY + 1, gridX + 1);
    wattron(gridw, COLOR_PAIR(color));
    waddch(gridw, ' ');
    wattroff(gridw, COLOR_PAIR(color));

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

void MainApp::createColorPicker() const {
    colorPickerw = newwin(pickerRows + 2, pickerCols + 2, 1, width + 4);
    box(colorPickerw, 0, 0);
    for (int y = 0; y < pickerRows; ++y) {
        for (int x = 0; x < pickerCols; ++x) {
            wattron(colorPickerw, COLOR_PAIR((y * pickerCols) + x + 1));
            wmove(colorPickerw, y + 1, x + 1);
            waddch(colorPickerw, ' ');
            wattroff(colorPickerw, COLOR_PAIR((y * pickerCols) + x + 1));
        }
    }

    wrefresh(colorPickerw);
    wrefresh(mainw);
}

void MainApp::changeColor() {
    currentColor = static_cast<Color>((pickerY * pickerCols) + pickerX + 1);
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
    init_pair(red_pair, COLOR_WHITE, COLOR_RED);
    init_pair(blue_pair, COLOR_WHITE, COLOR_BLUE);
    init_pair(green_pair, COLOR_WHITE, COLOR_GREEN);
    init_pair(yellow_pair, COLOR_WHITE, COLOR_YELLOW);
}