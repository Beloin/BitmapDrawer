#ifndef BITMAP_H
#define BITMAP_H

#include <cstdint>
#include <vector>

// Using pragma to force 16 bits storage
#pragma pack(push, 2)

struct bitmapheader {
  char header[2]{'2', 'M'};
  int32_t file_size;
  int32_t reserved{0};
  int32_t data_offset;
};

#pragma pack(pop)

struct bitmapinfo_header {
  int32_t header_size{40};
  int32_t width;
  int32_t height;
  int16_t planes{1};
  int16_t bits_per_pixel{24};
  int32_t compression{0};
  int32_t data_size{0};
  int32_t horizontal_resolution{2400};
  int32_t vertical_resolution{2400};
  int32_t colours{0};
  int32_t important_colours{0};
};

struct pixel {
  uint8_t blue;
  uint8_t green;
  uint8_t red;
}; // Microsoft by default uses BGR -- Unfortunately

class Bitmap {
private:
  int width{800};
  int height{600};
  std::vector<pixel> pixels;

public:
  Bitmap() : pixels(width * height) {}
  void SetPixel(int x, int y, pixel p);
  void SetRow(int row, pixel p);
  void SetAll(pixel p);
};


#endif // !BITMAP_H
