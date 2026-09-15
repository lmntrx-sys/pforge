CC = gcc
CFLAGS = -Wall -Wextra -g -fsanitize=address,undefined

pforge: main.c lexer.c chunk.c Token.c
	$(CC) $(CFLAGS) -o pforge main.c lexer.c chunk.c Token.c

clean:
	rm -f pforge