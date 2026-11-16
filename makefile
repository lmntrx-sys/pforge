CC = gcc
CFLAGS = -Wall -Wextra -g -fsanitize=address,undefined -Werror=format-security

pforge: main.c lexer.c ref_table.c Token.c
	$(CC) $(CFLAGS) -o pforge main.c lexer.c Token.c

clean:
	rm -f pforge