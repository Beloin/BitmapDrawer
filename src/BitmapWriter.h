#ifndef BITMAP_WRITER_H
#define BITMAP_WRITER_H

#include <string>

class BitmapWriter {
private:
    std::string filename;

public:
    explicit BitmapWriter(std::string filename) : filename(std::move(filename)) {}

    bool Write();
};

#endif // !BITMAP_WRITER_H
