#include <stdlib.h>
#include "common.h"
#include "lexer.h"
#include "Token.h"

static char* readFile(const char* path) {
    //  Open the file in binary mode
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Could not read file at \"%s\".\n", path);
        exit(64);
    }

    //  Seek to the end of the file to determine its size
    fseek(file, 0L, SEEK_END);
    long unsigned fileSize = ftell(file);
    rewind(file);

    // Allocate memory for the file content plus a null terminator
    char* buffer = (char*)malloc(fileSize+1);
    if (buffer == NULL) {
        fprintf(stderr, "Not enough memory in \"%s\".\n", path);
        exit(74);
    }
    // Read the file into the buffer
    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);

    //  Check if the entire file was read successfully
    if (bytesRead < fileSize) {
        fprintf(stderr, "Could not read file \"%s\".\n", path);
        exit(74);
    }
    buffer[bytesRead] = '\0';

    fclose(file);
    return buffer;

}


int main() {
    char* source = readFile("test.pf");
    if (source == NULL) return 1;

    int line = 1;
    int pos = 0;
    Token tok;

    // lex every token until EOF
    do
    {
        tok = lexerNextToken(source, &line, &pos);
        token_print(&tok);
        token_free(&tok);

    } while (tok.type != TOK_EOF && tok.type != TOK_ERROR);
    
    free(source);
    return 0;
}
