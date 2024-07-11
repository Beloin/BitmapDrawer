//
// Created by beloin on 03/07/24.
//

#ifndef BITMAP_MAINAPP_H
#define BITMAP_MAINAPP_H

#include "types.h"

enum CaretPlace {
    GRID, PICKER
};

class MainApp {
private:
    Status status{INACTIVE};
    CaretPlace currentCaretPlace{GRID};

    int width{100};
    int height{30};
    int gridX{0};
    int gridY{0};

    int pickerX{0};
    int pickerY{0};

    Color currentColor{WHITE};

    onSet onSet_{nullptr};
    onPosChange onPosChange_{nullptr};
    onSave onSave_{nullptr};

public:
    void initializeUI();

    void closeUI();

    void createGrid(int width_, int height_);

    void createColorPicker() const;

    [[noreturn]] void loop();

    void changeGridPos(int x, int y);

    void changePickerPos(int x, int y);

    void setPixel(Color color) const;

    void setSaveCallback(onSave cb);

    void setPosChangeCallback(onPosChange cb);

    void setOnSetCallback(onSet cb);

    void changeColor();

    void changeCaret();
};


#endif //BITMAP_MAINAPP_H
