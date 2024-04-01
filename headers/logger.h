#pragma once

enum level {DEBUG, TRACE, INFO, ERROR};
extern enum level CURRENT_LEVEL;

void log_(enum level l, const char* format, ...);
enum level set_log_level(enum level l);
