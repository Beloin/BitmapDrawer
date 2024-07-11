//
// Created by beloin on 04/07/24.
//

#ifndef BITMAP_COMMAND_H
#define BITMAP_COMMAND_H

#include <ncurses.h>

Command getCommand() {
    int c = getch();
    if (c == '\033') {   // if the first value is esc skip the [
        getch();
        switch (getch()) {
            case 'A':
                return UP;
            case 'B':
                return DOWN;
            case 'C':
                return RIGHT;
            case 'D':
                return LEFT;
        }
    }

    switch (c) {
        case '\n':
            return ENTER;
        case ' ':
            return SPACE;
        case 'h':
            return LEFT;
        case 'j':
            return DOWN;
        case 'k':
            return UP;
        case 'l':
            return RIGHT;
        case 'S':
        case 's':
            return SAVE;
        case 'c':
        case 'C':
            return CHANGE_CARET;
        default:
            return NONE;
    }
}



#endif //BITMAP_COMMAND_H
