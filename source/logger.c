#include <stdarg.h>
#include <stdio.h>

#include "../headers/logger.h"

enum level CURRENT_LEVEL = DEBUG;

void log_(enum level l, const char* format, ...)
{
    va_list ap;
    va_start(ap, format);

    if (l >= CURRENT_LEVEL)
    {
        vprintf(format, ap);
    }

    va_end(ap);

}

enum level set_log_level(enum level l)
{
    enum level previous = CURRENT_LEVEL;
    CURRENT_LEVEL = l;
    return previous;
}
