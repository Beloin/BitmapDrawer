//
// Created by beloin on 01/07/24.
//

#include <fstream>
#include "BitmapWriter.h"

bool BitmapWriter::Write(const std::string &filename_out) {
    auto lastFilename = this->filename;
    this->filename = filename_out;
    auto result = Write();
    this->filename = lastFilename;
    return result;
}

bool BitmapWriter::Write() {
    bitmapheader header;
    bitmapinfo_header infoHeader;

    size_t structsSize = sizeof(bitmapheader) + sizeof(bitmapinfo_header);
    header.file_size = structsSize +
                       (this->bitmap.width * this->bitmap.height) * sizeof(pixel);
    header.data_offset = structsSize;

    infoHeader.width = bitmap.width;
    infoHeader.height = bitmap.height;

    std::ofstream ofstream{filename, std::fstream::out | std::fstream::binary};

    if (!ofstream.is_open()) return false;

    ofstream.write(reinterpret_cast<char *>(&header), sizeof(bitmapheader));
    ofstream.write(reinterpret_cast<char *>(&infoHeader), sizeof(bitmapinfo_header));


    ofstream.write(reinterpret_cast<const char *>(bitmap.pixels.data()), bitmap.pixels.size() * sizeof(pixel));

    if (!ofstream.good()) return false;

    ofstream.close();

    return true;
}
