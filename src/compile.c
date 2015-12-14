#include <stdio.h>
#include "bcc.h"

void emitAdd(Token *left, Token *right)
{
	printf("add %d,%d\n", left->value.integer, right->value.integer);
}

void compile(Token *root)
{
	switch (root->type) {
		case '+':
			emitAdd(root->left, root->right);
			break;
	}
}
