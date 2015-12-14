#include <stdio.h>
#include "bcc.h"

#define TOKEN_STACK_SIZE	10

// Keeps a stack of tokens
static int tokenStackCount = 0;
static Token *tokenStack;

// Pop a token off the stack
Token *popToken()
{
	Token *t;
	if (tokenStackCount > 0) {
		t = tokenStack;
		tokenStack = tokenStack->next;
		tokenStackCount--;
	} else {
		t = getToken();
	}
	printf("Token: %d\n", t->type);
	return t;
}

// Push a token back onto the stack
void pushToken(Token *t)
{
	if (tokenStackCount == 10) {
		error("Attempted to push too many tokens onto the stack");
	} else {
		t->next = tokenStack;
		tokenStack = t;
		tokenStackCount++;
	}
}

Token *buildExpression(Token *token1)
{
	Token *token2 = popToken();
	Token *token3;

	switch (token2->type) {
		case '+':
		case '-':
		case '/':
		case '*':
			token2->left = token1;
			token3 = popToken();
			token2->right = token3;
	}
	return token2;
}


// Main routine for the parser
void parse()
{
	Token *root, *token;
	do {
		token = popToken();
		switch (token->type) {
			case T_INTEGER:
				root = buildExpression(token);
				break;
		}
	} while (token->type != EOF);
	compile(root);
}
