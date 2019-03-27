#include "lexer.h"
#include <stdlib.h>
#include <stdio.h>
#include <lexer.h>


char BUFFER[2 * MAX_BUFFER_SIZE + 2];

char *forward = (char *) BUFFER;
char *lexeme_begin = (char *) BUFFER;

const char *RELOP_LE = "LE";
const char *RELOP_NE = "NE";
const char *RELOP_LT = "LT";
const char *RELOP_EQ = "EQ";
const char *RELOP_GE = "GE";
const char *RELOP_GT = "GT";
const char *ASSIGN = "ASSIGN";


short FINISH = 0;