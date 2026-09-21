#include "common.h"
#include "Token.h"
#include <stdlib.h>

#include "lexer.h"

void token_free(Token* tok) {
    switch (tok->type) {
        case TOK_IDENT:
        case TOK_STRING_LIT:
        case TOK_ERROR:
            free(tok->value.string);
            tok->value.string = NULL;
            break;
        default:
            break;
    }
}

void token_print(const TokenType type) {
  switch (type) {
      case TOK_LBRACE:
          printf("TOKEN '{' \n");
          break;

      case TOK_IDENT:
          printf("TOKEN 'IDENT' \n");
          break;

        case TOK_STRING_LIT:
          printf("TOKEN 'STRING_LIT' \n");
          break;

        case TOK_DEC_LIT:
          printf("TOKEN 'DEC_LIT' \n");
          break;

        case TOK_HEX_LIT:
            printf("TOKEN 'HEX_LIT' \n");
            break;

        case TOK_MAC_LIT:
            printf("TOKEN 'MAC_LIT' \n");
            break;

        case TOK_IP_LIT:
            printf("TOKEN 'IP_LIT' \n");
            break;
        
        case TOK_U8:
            printf("TOKEN 'U8' \n");
            break;

        case TOK_U16BE:
            printf("TOKEN 'U16BE' \n");
            break;

        case TOK_U16LE:
            printf("TOKEN 'U16LE' \n");
            break;

        case TOK_U32BE:
            printf("TOKEN 'U32BE' \n");
            break;

        case TOK_U32LE:
            printf("TOKEN 'U32LE' \n");
            break;

        case TOK_STR:
            printf("TOKEN 'STR' \n");
            break;

        case TOK_COMPUTED:
            printf("TOKEN 'COMPUTED' \n");
            break;

        case TOK_PACKET:
            printf("TOKEN 'PACKET' \n");
            break;
        
        case TOK_RBRACE:
            printf("TOKEN '}' \n");
            break;

        case TOK_LBRACKET:
            printf("TOKEN '[' \n");
            break;

        case TOK_RBRACKET:
            printf("TOKEN ']' \n");
            break;

        case TOK_EQUALS:
            printf("TOKEN '=' \n");
            break;

        case TOK_SEMICOLON:
            printf("TOKEN ';' \n"); 
            break;

        case TOK_ERROR:
            printf("TOKEN 'ERROR' \n");
            break;  

        case TOK_EOF:
            printf("TOKEN 'EOF' \n");
            break;
            
      default:
          printf("TOKEN{UNKNOWN}");
          break;
  }
}

