#include "bitmap.h"

void Bitmap::SetPixel(int x, int y, pixel p) {
  int index = y * width + x;
  pixels[index] = p;
}

void Bitmap::SetRow(int row, pixel p) {
  for (int i = 0; i < width; i++) {
    SetPixel(i, row, p);
  }
}

void Bitmap::SetAll(pixel p) {
  for (int i = 0; i < height; i++) {
    SetRow(i, p);
  }
}
