#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED


#include <stdlib.h>

#define MAX_BUFFER_SIZE 2048

extern char BUFFER[2 * MAX_BUFFER_SIZE + 2];

#define L MAX_BUFFER_SIZE
#define R 2 * MAX_BUFFER_SIZE + 1

extern char *forward;
extern char *lexeme_begin;

extern const char *RELOP_LE;
extern const char *RELOP_NE;
extern const char *RELOP_LT;
extern const char *RELOP_EQ;
extern const char *RELOP_GE;
extern const char *RELOP_GT;
extern const char *ASSIGN;

extern short FINISH;

#define TOKEN_ID 1
#define TOKEN_KEY 0
#define TOKEN_NUMBER 2
#define TOKEN_STR 3
#define TOKEN_RELOP_LE 4
#define TOKEN_RELOP_NE 5
#define TOKEN_RELOP_LT 6
#define TOKEN_RELOP_EQ 7
#define TOKEN_RELOP_GE 8
#define TOKEN_RELOP_GT 9
#define TOKEN_ASSIGN 10
#define TOKEN_BLANK 11

struct Token {
    short type;
    char *name;
};

#define INIT_SUCCESS 0

extern short lexer_init();

#define HAVE_TOKEN 0

extern short get_next_token(struct Token *);


extern void fail();

#define letter isalpha(*forward)
#define digit isdigit(*forward)
#define blank isblank(*forward)
#define space isspace(*forward)
#define dot *forward == '.'
#define E *forward == 'E'
#define lexeme_length __lexeme_length()
#define or ||
#define and &&
#define is ==

extern void id_and_keyword_token(struct Token *);

extern void number_token(struct Token *);

extern void blank_token(struct Token *token);

extern int __lexeme_length();

extern void relop_token(struct Token *);

#endif // LEXER_H_INCLUDED
