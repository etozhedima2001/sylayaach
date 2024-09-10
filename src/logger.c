#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static FILE *log_file = NULL;

void log_init(const char *filename) {
    log_file = fopen(filename, "a");
    if (!log_file) {
        fprintf(stderr, "Не удалось открыть файл лога: %s\n", filename);
        exit(1);
    }
}

void logcat(LogLevel level, const char *message) {
    if (!log_file) {
        fprintf(stderr, "Лог файл не инициализирован\n");
        return;
    }

    const char *level_strings[] = { "DEBUG", "INFO", "WARNING", "ERROR" };

    // Получаем текущее время
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    // Формат времени: YYYY-MM-DD HH:MM:SS
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", t);

    // Записываем в лог
    fprintf(log_file, "[%s] [%s] %s\n", time_str, level_strings[level], message);
    fflush(log_file);
}

void log_close() {
    if (log_file) {
        fclose(log_file);
        log_file = NULL;
    }
}
