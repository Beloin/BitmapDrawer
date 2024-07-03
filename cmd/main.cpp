#include <iostream>

#include "bitmap.h"
#include "BitmapWriter.h"

int main(int argc, char *argv[]) {
    std::cout << "Hello World" << std::endl;
    Bitmap bmp{};

    // Default row
    for (int i = 0; i < 800; i+=2) {
        bmp.SetRow(1, pixel{127, 127, 127});
    }

    BitmapWriter writer = bmp; // Implicit conversion, sweet but dangerous
    writer.Write("../mein.BMP");

    return 0;
}
