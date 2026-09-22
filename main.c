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
    long unsigned fileSize = ftell(file);
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


int main() {
    char* source = readFile("test.pf");
    if (source == NULL) return 1;

    int line = 1;
    int pos = 0;
    Token tok;

    // lex every token until EOF
    do
    {
        lexerNextToken(source, &line, &pos);
        token_print(&tok);
        token_free(&tok);

    } while (tok.type != TOK_EOF && tok.type == TOK_ERROR);
    
    free(source);
    return 0;
}
