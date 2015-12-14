#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "bcc.h"

// Keeps track of what line number we're on, start on line 1.
int lineNumber = 1;

// This holds a single character buffer so that we can simulate
// pushing a character back into the input.  The lexer doesn't 
// need to push more than one character.
static bool charBufferAvailable = false;
static int charBufferContents;

// Get a single character from the input, if a character is available
// in the buffer, read that first.
int get()
{
	int c;
	if (charBufferAvailable == true) {
		charBufferAvailable = false;
		c = charBufferContents;
	} else {
		c = getc(stdin);
	}
	
	// Update the line number 
	if (c == '\n') {
		lineNumber++;
	}

	return c;
}

// Push a single character back into the input.  Puts the character
// into the buffer. get() will pick it up on its next call.
void unget(int c)
{
	charBufferContents = c;
	charBufferAvailable = true;

	// If we pushed back a \n, then we're going back
	// up a line
	if (c == '\n') {
		lineNumber--;
	}
}

// Read a number
unsigned long long read_integer()
{
	int c;
	unsigned long long n = 0;

	c = get();
	while (isdigit(c)) {
		n = (n * 10) + (c - '0');
		c = get();
	};
	return n;
}

char *read_string()
{
	int c, length = 0, chunks = 1;
	char *str, *p;

	str = p = malloc(256);
	c = get();
	while (c != '\"' && c != EOF) {
		*p++ = c;
		// If the buffer is full, make it bigger
		if (p - str >= 254 * chunks) {
			length = p - str;
			chunks++;
			str = realloc(str, chunks * 256);
			p = str + length;
		}
		c = get();
	}
	*p = 0;
	if (c == EOF) {
		error("Missing trailing `\"` in string");
	}
	return str;
}

// This is the main lexer function.  It reads the input and
// returns a token
Token lex()
{
	int c;
	Token token;

top:
	c = get();
	switch(c) {
		case '\n':
			lineNumber++;
		case ' ':
		case '\t':
			goto top;
		case '0': case '1': case '2': case '3':
		case '4': case '5': case '6': case '7':
		case '8': case '9':
			unget(c);
			token.type = T_INTEGER;
			token.value.integer = read_integer();
			break;
		case '\"':
			token.type = T_STRING;
			token.value.string = read_string();
			break;
		default:
			token.type = c;
	}

	return token;
}
