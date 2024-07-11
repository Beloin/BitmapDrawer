//
// Created by beloin on 07/07/24.
//

#include "types.h"

pixel colorToPixel(Color color) {
    switch (color) {
        case WHITE:
            return {255, 255, 255};
        case BLACK:
            return {0, 0, 0};
        case RED:
            return {0, 0, 255};
        case BLUE:
            return {255, 0, 0};
        case GREEN:
            return {0, 255, 0};
        case YELLOW:
            return {0, 255, 255};
        default:
            return {255, 255, 255};
    }
}

std::string colorToString(Color color) {
    switch (color) {
        case WHITE:
            return "WHITE";
        case BLACK:
            return "BLACK";
        case RED:
            return "RED";
        case BLUE:
            return "BLUE";
        case GREEN:
            return "GREEN";
        case YELLOW:
            return "YELLOW";
        default:
            return "UNDEFINED";
    }
}