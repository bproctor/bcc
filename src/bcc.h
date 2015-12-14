#ifndef BCC_H__
#define BCC_H__

// this defines all the tokens, single character tokens like + and -
// are just the characters themselves.
enum {
	T_INTEGER = 1000,
	T_STRING,
};

// Holds a token
typedef struct Token {
	int type;
	union {
		unsigned long long integer;
		char *string;
	} value;
} Token;

extern int lineNumber;

extern void error(const char *fmt, ...);
extern Token lex();
extern void parse();

#endif
