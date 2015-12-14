#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "bcc.h"

FILE *infile;
const char *inname;
FILE *outfile;
const char *outname;

// Report an error and kill the compiler
void error(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, "error:%d: ", lineNumber);
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(1);
}

// Main entry point
int main(int argc, const char **argv)
{
	if (argc == 2) {
		inname = argv[1];
		if ((infile = fopen(inname, "r")) == NULL) {
			fprintf(stderr, "Could not open `%s` for reading.", inname);
			return 1;
		}
	} else {
		infile = stdin;
	}
	parse();
	return 0;
}
