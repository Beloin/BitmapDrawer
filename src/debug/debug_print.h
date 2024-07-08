//
// Created by beloin on 07/07/24.
//

#ifndef BITMAP_DEBUG_PRINT_H
#define BITMAP_DEBUG_PRINT_H

#include <fstream>

#define DEBUG_FILE "../dbg.log"

std::ofstream debugOut;


namespace Debug {

    bool start();

    void stop();

    void dprint(std::string const &_format, ...);
}

#endif //BITMAP_DEBUG_PRINT_H
