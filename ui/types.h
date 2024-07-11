//
// Created by beloin on 04/07/24.
//

#ifndef BITMAP_TYPES_H
#define BITMAP_TYPES_H

#include "../src/bitmap.h"
#include <string>

enum Status {
    ACTIVE,
    INACTIVE
};

enum Color {
    BLACK = 1,
    WHITE = 2,
    RED,
    BLUE,
    GREEN,
    YELLOW
};

enum Command {
    ENTER, SPACE,
    UP, DOWN, RIGHT, LEFT,
    SAVE, CHANGE_CARET,
    NONE
};

typedef void (*onSet)(Color color, int x, int y);

typedef void (*onPosChange)(int x, int y);

typedef void (*onSave)();

pixel colorToPixel(Color color);

std::string colorToString(Color color);


#endif //BITMAP_TYPES_H
