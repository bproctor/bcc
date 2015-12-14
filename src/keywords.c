#include "bcc.h"

static Keyword a_keywords[] = {
	{"auto", T_AUTO},
	{0, 0},
};

static Keyword b_keywords[] = {
	{"break", T_BREAK},
	{0, 0},
};

static Keyword c_keywords[] = {
	{"case", T_CASE},
	{"char", T_CHAR},
	{"const", T_CONST},
	{"continue", T_CONTINUE},
	{0, 0},
};

static Keyword d_keywords[] = {
	{"default", T_DEFAULT},
	{"do", T_DO},
	{"double", T_DOUBLE},
	{0, 0},
};

static Keyword e_keywords[] = {
	{"else", T_ELSE},
	{"enum", T_ENUM},
	{"extern", T_EXTERN},
	{0, 0},
};

static Keyword f_keywords[] = {
	{"float", T_FLOAT},
	{"for", T_FOR},
	{0, 0},
};

static Keyword g_keywords[] = {
	{"goto", T_GOTO},
	{0, 0},
};

static Keyword i_keywords[] = {
	{"if", T_IF},
	{"int", T_INT},
	{0, 0},
};

static Keyword l_keywords[] = {
	{"long", T_LONG},
	{0, 0},
};

static Keyword r_keywords[] = {
	{"register", T_REGISTER},
	{"return", T_RETURN},
	{0, 0},
};

static Keyword s_keywords[] = {
	{"short", T_SHORT},
	{"signed", T_SIGNED},
	{"sizeof", T_SIZEOF},
	{"static", T_STATIC},
	{"struct", T_STRUCT},
	{"switch", T_SWITCH},
	{0, 0},
};

static Keyword t_keywords[] = {
	{"typedef", T_TYPEDEF},
	{0, 0},
};

static Keyword u_keywords[] = {
	{"union", T_UNION},
	{"unsigned", T_UNSIGNED},
	{0, 0},
};

static Keyword v_keywords[] = {
	{"void", T_VOID},
	{"volatile", T_VOLATILE},
	{0, 0},
};

static Keyword w_keywords[] = {
	{"while", T_WHILE},
	{0, 0},
};

Keyword *keywords[26] = {
	a_keywords, b_keywords, c_keywords, d_keywords, e_keywords,
	f_keywords, g_keywords, 0,          i_keywords, 0,
	0,          l_keywords, 0,          0,          0,
	0,          0,          r_keywords, s_keywords, t_keywords,
	u_keywords, v_keywords, w_keywords, 0,        0,
	0,
 };
