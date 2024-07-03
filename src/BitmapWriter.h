#ifndef BITMAP_WRITER_H
#define BITMAP_WRITER_H

#include <string>
#include "bitmap.h"

class BitmapWriter {
private:
    std::string filename;
    const Bitmap& bitmap;

public:
    BitmapWriter(std::string filename, const Bitmap& bitmap) : filename(std::move(filename)), bitmap(bitmap) {}

    BitmapWriter(const Bitmap& bitmap) : filename("./btm.BMP"), bitmap(bitmap) {}

    bool Write();
    bool Write(const std::string &filename_out);
};

#endif // !BITMAP_WRITER_H
