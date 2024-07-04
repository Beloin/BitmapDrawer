//
// Created by beloin on 03/07/24.
//

#ifndef BITMAP_MAINAPP_H
#define BITMAP_MAINAPP_H

enum Status {
    ACTIVE,
    INACTIVE
};

class MainApp {
private:
    Status status;
public:
    void initializeUI();
    void closeUI();
    void createGrid(int width, int height);
};


#endif //BITMAP_MAINAPP_H
