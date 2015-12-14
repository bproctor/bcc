#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "bcc.h"

// Report an error and kill the compiler
void error(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(1);
}

// Main entry point
int main(int argc, const char **argv)
{
	parse();
	return 0;
}
