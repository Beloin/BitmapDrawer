//
// Created by beloin on 07/07/24.
//

#include "debug_print.h"
#include <cstdarg>

int extractFormatCount(const std::string &_format);

bool Debug::start() {
    debugOut.open(DEBUG_FILE, std::ios_base::out | std::ios_base::app);
    return debugOut.is_open();
}

void Debug::dprint(const std::string &_format, ...) {
    char res[_format.size()];
    va_list ptr;

    va_start(ptr, _format);
    vsprintf(res, _format.c_str(), ptr);

    va_end(ptr);
}

int extractFormatCount(const std::string &_format) {
    int count;
    size_t inIndex = 0;
    size_t fiIndex = _format.size() - 1;
    while (inIndex != fiIndex) {
        if (_format[inIndex] == '%') {
            if (inIndex!= )
        }

        if (_format[fiIndex] == '%') {

        }

        inIndex++;
        fiIndex--;
    }

    return count;
}