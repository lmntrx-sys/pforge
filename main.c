#include <stdlib.h>
#include "common.h"
#include "lexer.h"
#include "Token.h"

static char* readFile(const char* path) {
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Could not read file at \"%s\".\n", path);
        exit(64);
    }

    fseek(file, 0L, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(fileSize+1);
    if (buffer == NULL) {
        fprintf(stderr, "Not enough memory in \"%s\".\n", path);
        exit(74);
    }
    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);

    if (bytesRead < fileSize) {
        fprintf(stderr, "Could not read file \"%%\".\n");
        exit(74);
    }
    buffer[bytesRead] = '\0';

    fclose(file);
    return buffer;

}

static void runFile(const char* path) {
    char* source = readFile(path);
    //TODO: pass source to the lexer.

    int *pos = 0;
    int *line = 0;

    Token token = lexerNextToken(source, line, pos);

    //token_free(token);
}

static void repl() {
    //TODO: interactive mode - read a line, lex it, print tokens
    printf("repl not implemented yet");
}

int main() {
    // initVm()

    //if (argc == 1){ repl(); }
    //else if (argc == 2) {
        //runFile(argv[1]);

    //} else {
    //    fprintf(stderr, "Usage path [pforge]");
    //   exit(74);
    //}

    // FreeVm
    //return 0;
    const TokenType token =  matchKeyword("packet", 6);
    return token;
}
