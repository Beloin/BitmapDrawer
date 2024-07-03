#include <iostream>

#include "bitmap.h"
#include "BitmapWriter.h"

int main(int argc, char *argv[]) {
    std::cout << "Hello World" << std::endl;
    Bitmap bmp{};

    bmp.SetAll({255, 255, 255});

    // Default row
    for (int i = 0; i < 600; i+=2) {
        bmp.SetRow(i, pixel{127, 127, 127});
    }

    BitmapWriter writer = bmp; // Implicit conversion, sweet but dangerous
    writer.Write("../mein.BMP");

    return 0;
}
