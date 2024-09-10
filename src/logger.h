#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

// Уровни логирования
typedef enum {
    DEBUG,
    INFO,
    WARNING,
    ERROR
} LogLevel;

void log_init(const char *filename);
void logcat(LogLevel level, const char *message);
void log_close();

#endif // LOGGER_H
