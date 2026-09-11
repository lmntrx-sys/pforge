#include <stdlib.h>
#include <string.h>

#include "common.h"

static char* readFile(const char* path) {
    FILE* file = fopen(path, "rb");

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(fileSize+1);
    size_t bytesRead = fread(file, sizeof(char), fileSize, file);
    buffer[bytesRead] = '\0';

    fclose(file);
    return buffer;

}

int main(int argc, const char* argv[]) {
    // initVm()
    if (argc == 1){ repl(); }
    else if (argc == 2) {
        runFile(argv[1]);

    } else {
        fprintf(stderr, "Usage path [pforge]");
        exit(64);
    }

    // FreeVm
    return 0;
}
