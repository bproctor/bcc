#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
unsigned long long read_integer(int first)
{
	int c;
	unsigned long long n = 0;

	c = first;
	while (isdigit(c)) {
		n = (n * 10) + (c - '0');
		c = get();
	};
	return n;
}

// Reads a string and returns a pointer to it.
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

// Looks up a keyword in the keyword table and return the tokenid.  If one is
// not found, then return 0.
int lookup_keyword(const char *str)
{
	Keyword *k = keywords[*str + 'a'];
	while (k) {
		if (!strcmp(k->name, str)) {
			return k->token;
		}
		++k;
	}
	return 0;
}

// Reads an identified and returns a pointer to it.  This is essentially the
// same as read_string except we check for a different set of characters.
char *read_identifier(int first)
{
	int c, length = 0, chunks = 1;
	char *str, *p;

	str = p = malloc(256);
	c = first;
	while (isalnum(c) || c == '_') {
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
	// Push the last character back since it's not part of the identified
	unget(c);
	return str;
}

// This is the main lexer function.  It reads the input and
// returns a token
Token lex()
{
	int c;
	char *str;
	Token token;

top:
	c = get();
	switch(c) {
		case '\n':
			lineNumber++;
		case ' ':
		case '\t':
			goto top;
		case 'a': case 'b': case 'c': case 'd':
		case 'e': case 'f': case 'g': case 'i':
		case 'l': case 'r': case 's': case 't':
		case 'u': case 'v': case 'w':
			// These letters could indicate the beginning of a reserved word
			// rather than an identifier, check the keywords first.
			str = read_identifier(c);
			token.type = lookup_keyword(str);
			if (token.type == 0) {
				token.type = T_IDENTIFIER;
				token.value.string = str;
			} else {
				// Don't need to save the actual string anymore
				// if it's a reserved word so free the memory
				free(str);
			}
			break;
		case 'h': case 'j': case 'k': case 'm':
		case 'n': case 'o': case 'p': case 'q':
		case 'x': case 'y': case 'z': case 'A':
		case 'B': case 'C': case 'D': case 'E':
		case 'F': case 'G': case 'H': case 'I':
		case 'J': case 'K': case 'L': case 'M':
		case 'N': case 'O': case 'P': case 'Q':
		case 'R': case 'S': case 'T': case 'U':
		case 'V': case 'W': case 'X': case 'Y':
		case 'Z': case '_':
			// Anthing that starts with one of these characters is an identified
			// and not a keyword.
			token.type = T_IDENTIFIER;
			token.value.string = read_identifier(c);
			break;
		case '0': case '1': case '2': case '3':
		case '4': case '5': case '6': case '7':
		case '8': case '9':
			token.type = T_INTEGER;
			token.value.integer = read_integer(c);
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
