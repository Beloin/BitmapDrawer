//
// Created by beloin on 03/07/24.
//


#include "bitmap.h"
#include "BitmapWriter.h"

#define CPP_HEIGHT 600
#define CPP_WIDTH 100

void MakeAnPlus(Bitmap &cppBmp, int middleW, int middleH);

void CreateCppSymbol() {
    Bitmap cppBmp;
    cppBmp.SetAll({255, 255, 255});
    for (int i = 0; i < CPP_WIDTH; ++i) {
        for (int j = 0; j < CPP_HEIGHT; ++j) {
            cppBmp.SetPixel(i, j, {127, 127, 80});
        }
    }

    for (int i = CPP_WIDTH; i < CPP_WIDTH * 4; ++i) {
        for (int j = 0; j < CPP_WIDTH; ++j) {
            cppBmp.SetPixel(i, j, {127, 127, 80});
        }
    }

    for (int i = CPP_WIDTH; i < CPP_WIDTH * 4; ++i) {
        for (int j = cppBmp.getHeight(); j > cppBmp.getHeight() - CPP_WIDTH; --j) {
            cppBmp.SetPixel(i, j, {127, 127, 80});
        }
    }

    int middleW = cppBmp.getWidth() / 2;
    int middleH = cppBmp.getHeight() / 2;
    MakeAnPlus(cppBmp, middleW, middleH);

    middleW += middleW / 2 + 50;
    MakeAnPlus(cppBmp, middleW, middleH);

    BitmapWriter{cppBmp}.Write("../cpp.bmp");
}

void MakeAnPlus(Bitmap &cppBmp, int middleW, int middleH) {
    for (int i = middleW - CPP_WIDTH; i < middleW + CPP_WIDTH; ++i) {
        for (int j = middleH - CPP_WIDTH / 3; j < middleH + CPP_WIDTH / 3; ++j) {
            cppBmp.SetPixel(i, j, {127, 127, 80});
        }
    }

    for (int i = middleW - CPP_WIDTH / 3; i < middleW + CPP_WIDTH / 3; ++i) {
        for (int j = middleH - CPP_WIDTH; j < middleH + CPP_WIDTH; ++j) {
            cppBmp.SetPixel(i, j, {127, 127, 80});
        }
    }
}
