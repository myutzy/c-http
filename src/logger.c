#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

void log_message(const char *level, const char *format, ...) {
    // Get the current timestamp
    time_t rawtime;
    char time_buffer[20];
    time(&rawtime);
    const struct tm *timeinfo = localtime(&rawtime);
    strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

    // Create the log message
    char message_buffer[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(message_buffer, sizeof(message_buffer), format, args);
    va_end(args);

    // Print the log message to the console
    printf("[%s] [%s] %s\n", time_buffer, level, message_buffer);

    // Create the log directory if it doesn't exist
    system("mkdir -p ../logs");

    // Generate the log file path based on the current date
    char log_file_path[256];
    strftime(log_file_path, sizeof(log_file_path), "../logs/%Y-%m-%d.txt", timeinfo);

    // Open the log file and write the log message
    FILE *log_file = fopen(log_file_path, "a");
    if (log_file) {
        fprintf(log_file, "[%s] [%s] %s\n", time_buffer, level, message_buffer);
        fclose(log_file);
    }
}
