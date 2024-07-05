//
// Created by beloin on 04/07/24.
//

#ifndef BITMAP_TYPES_H
#define BITMAP_TYPES_H

enum Status {
    ACTIVE,
    INACTIVE
};

enum Color {
    WHITE,
    BLACK
};

enum Command {
    ENTER, SPACE,
    UP, DOWN, RIGHT, LEFT,
    NONE
};

typedef void (*onSet)(Color color, int x, int y);
typedef void (*onPosChange)(int x, int y);
typedef void (*onSave)();


#endif //BITMAP_TYPES_H
