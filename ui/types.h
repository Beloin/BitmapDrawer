//
// Created by beloin on 04/07/24.
//

#ifndef BITMAP_TYPES_H
#define BITMAP_TYPES_H

#include "../src/bitmap.h"

enum Status {
    ACTIVE,
    INACTIVE
};

enum Color {
    WHITE,
    BLACK,
    RED,
    BLUE,
    GREEN,
    YELLOW
};

enum Command {
    ENTER, SPACE,
    UP, DOWN, RIGHT, LEFT,
    NONE
};

typedef void (*onSet)(Color color, int x, int y);

typedef void (*onPosChange)(int x, int y);

typedef void (*onSave)();

pixel colorToPixel(Color color);


#endif //BITMAP_TYPES_H
