//
// Created by beloin on 07/07/24.
//

#include "debug_print.h"
#include <cstdarg>

static std::ofstream debugOut;

int extractFormatCount(const std::string &_format);

bool Debug::start() {
    debugOut.open(DEBUG_FILE);
    return debugOut.is_open();
}

void Debug::dprint(const std::string &_format, ...) {
    char res[_format.size()];
    va_list ptr;

    va_start(ptr, _format);
    vsprintf(res, _format.c_str(), ptr);

    debugOut << res;
    debugOut.flush();
    va_end(ptr);
}

int extractFormatCount(const std::string &_format) {
    int count{0};
    size_t inIndex = 0;
    unsigned long size = _format.size();
    size_t fiIndex = size - 1;
    unsigned long mid = size / 2; // a%c, ab%dc
    while (inIndex <= mid) {
        if (_format[inIndex] == '%') {
            if (inIndex <= mid && _format[inIndex + 1] != '%') { count++; }
        }

        if (fiIndex > mid && _format[fiIndex] == '%') {
            if (fiIndex < size - 1 && _format[fiIndex + 1] != '%') {
                count++;
            }
        }

        inIndex++;
        fiIndex--;
    }

    return count;
}

void Debug::stop() {
    debugOut.close();
}