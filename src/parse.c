#include <stdio.h>
#include "bcc.h"

// Main routine for the parser
void parse()
{
	Token token;
	do {
		token = lex();
		if (token.type == T_INTEGER) {
			printf("Integer: %llu\n", token.value.integer);
		} else if (token.type == T_STRING) {
			printf("String: %s\n", token.value.string);
		} else if (token.type == T_IDENTIFIER) {
			printf("Identifier: %s\n", token.value.string);
		} else {
			printf("Token: %d\n", token.type);
		}
	} while (token.type != EOF);
}
