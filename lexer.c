#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "lexer2.h"

// global buffer size
int bufferSize;

// global two buffers
char *buf1, *buf2;

// begin and finish pointers for the two buffers
int begin, end;

// line number
int lineNumber = 1;
