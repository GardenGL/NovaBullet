#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define MAX_TEXT_BUFFER_LENGTH 1024
const char *TextFormat(const char *text, ...)
{
#ifndef MAX_TEXTFORMAT_BUFFERS
#define MAX_TEXTFORMAT_BUFFERS 4 // Maximum number of static buffers for text formatting
#endif

    // We create an array of buffers so strings don't expire until MAX_TEXTFORMAT_BUFFERS invocations
    static char buffers[MAX_TEXTFORMAT_BUFFERS][MAX_TEXT_BUFFER_LENGTH] = {0};
    static int index = 0;

    char *currentBuffer = buffers[index];
    memset(currentBuffer, 0, MAX_TEXT_BUFFER_LENGTH); // Clear buffer before using

    va_list args;
    va_start(args, text);
    vsprintf(currentBuffer, text, args);
    va_end(args);

    index += 1; // Move to next buffer for next function call
    if (index >= MAX_TEXTFORMAT_BUFFERS)
        index = 0;

    return currentBuffer;
}