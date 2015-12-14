#ifndef BCC_H__
#define BCC_H__

// this defines all the tokens, single character tokens like + and -
// are just the characters themselves.
enum {
	T_IDENTIFIER = 1000,
	T_INTEGER,
	T_STRING,

	// Operators
	T_ANDE,		// &=
	T_ADDE,		// +=
	T_COME,		// ~=
	T_DAND,		// &&
	T_DEC,		// --
	T_DEQ,		// ==
	T_DIVE,		// /=
	T_DOR,		// ||
	T_GE,		// >=
	T_INC,		// ++
	T_LE,		// <=
	T_MODE,		// %=
	T_MULE,		// *=
	T_NE,		// !=
	T_ORE,		// |=
	T_PTR,		// ->
	T_SHL,		// <<
	T_SHLE,		// <<=
	T_SHR,		// >>
	T_SHRE,		// >>=
	T_SUBE,		// -=
	T_XORE,		// ^=

	// Reserved words
	T_AUTO,
	T_BREAK,
	T_CASE,
	T_CHAR,
	T_CONST,
	T_CONTINUE,
	T_DEFAULT,
	T_DO,
	T_DOUBLE,
	T_ELSE,
	T_ENUM,
	T_EXTERN,
	T_FLOAT,
	T_FOR,
	T_GOTO,
	T_IF,
	T_INT,
	T_LONG,
	T_REGISTER,
	T_RETURN,
	T_SHORT,
	T_SIGNED,
	T_SIZEOF,
	T_STATIC,
	T_STRUCT,
	T_SWITCH,
	T_TYPEDEF,
	T_UNION,
	T_UNSIGNED,
	T_VOID,
	T_VOLATILE,
	T_WHILE,
};

// Holds a token
typedef struct Token {
	int type;
	union {
		unsigned long long integer;
		char *string;
	} value;
	struct Token *left;
	struct Token *right;
	struct Token *next;
} Token;

typedef struct Keyword {
	const char *name;
	int token;
} Keyword;

extern Keyword *keywords[26];
extern int lineNumber;
extern FILE *infile;
extern FILE *outfile;

extern void error(const char *fmt, ...);
extern Token *getToken();
extern void parse();
extern void compile(Token *);

#endif
