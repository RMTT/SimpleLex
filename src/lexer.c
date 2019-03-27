#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "lexer.h"

void __load_input(short which) {
    char *pos = "";
    if (which is 0)
        pos = BUFFER;
    else if (which is 1)
        pos = BUFFER + MAX_BUFFER_SIZE + 1;

    while (*pos != EOF)
        *pos++ = (char) getchar();
}

short lexer_init() {
    *(BUFFER + L) = EOF;
    *(BUFFER + R) = EOF;
    __load_input(0);
    return INIT_SUCCESS;
}


void __backward() {
    --forward;
}

void fail() {
    //printf("Lex error\n");
    //exit(0);
}

int __lexeme_length() {
    int l = (int) ((forward - lexeme_begin) / sizeof(char));
    if (l >= 0) {
        if ((lexeme_begin - BUFFER) / sizeof(char) <= MAX_BUFFER_SIZE and
            (forward - BUFFER) / sizeof(char) > MAX_BUFFER_SIZE)
            l--;
    } else {
        l = (int) ((forward - BUFFER) / sizeof(char) +
                   (BUFFER + 2 * MAX_BUFFER_SIZE + 1 - lexeme_begin) / sizeof(char));
    }
    return l;
}

void __forward() {
    switch (*++forward) {
        case EOF:
            if ((forward - BUFFER) / sizeof(char) is L) {
                __load_input(1);
            } else if ((forward - BUFFER) / sizeof(char) is R) {
                __load_input(0);
                forward = BUFFER;
            } else {
                FINISH = 1;
            }
            break;
        default:
            break;
    }
}

void id_and_keyword_token(struct Token *token) {
    short state = 0;

    while (1) {
        switch (state) {
            case 0:
                if (letter)
                    state = 1;
                else
                    fail();
                break;
            case 1:
                if (letter or digit)
                    state = 1;
                else
                    state = 2;
                break;

            default:
                break;
        }

        if (state is 2) {
            token->name = malloc(sizeof(char) * lexeme_length);
            token->type = TOKEN_ID;
            strncpy(token->name, lexeme_begin, (size_t) lexeme_length);
            __backward();
            break;
        }
        __forward();
    }
}

void number_token(struct Token *token) {
    short state = 0;

    while (1) {
        switch (state) {
            case 0:
                if (digit)
                    state = 1;
                else
                    fail();
                break;
            case 1:
                if (digit)
                    state = 1;
                else if (dot)
                    state = 2;
                else if (E)
                    state = 4;
                else
                    state = 7;
                break;
            case 2:
                if (digit)
                    state = 3;
                else
                    fail();
                break;
            case 3:
                if (digit)
                    state = 3;
                else if (E)
                    state = 4;
                else
                    state = 7;
                break;
            case 4:
                if (*forward is '+' || *forward is '-')
                    state = 5;
                else if (digit)
                    state = 6;
                else
                    fail();
                break;
            case 5:
                if (digit)
                    state = 6;
                else
                    fail();
            case 6:
                if (digit)
                    state = 6;
                else
                    state = 7;
            default:
                break;
        }
        if (state is 7) {
            token->name = malloc(sizeof(char) * lexeme_length);
            token->type = TOKEN_NUMBER;
            strncpy(token->name, lexeme_begin, (size_t) lexeme_length);
            __backward();
            break;
        }
        __forward();
    }
}

void blank_token(struct Token *token) {
    short state = 0;

    while (1) {
        switch (state) {
            case 0:
                if (blank or space)
                    state = 1;
                break;
            case 1:
                if (blank or space)
                    state = 1;
                else
                    state = 2;
                break;
            default:
                break;
        }
        if (state is 2) {
            token->type = TOKEN_BLANK;
            token->name = token->name = malloc(sizeof(char) * lexeme_length);
            strncpy(token->name, lexeme_begin, (size_t) lexeme_length);
            __backward();
            break;
        }
        __forward();
    }
}

void relop_token(struct Token *token) {
    short state = 0;

    while (1) {
        switch (state) {
            case 0:
                if (*forward is '<')
                    state = 1;
                else if (*forward is '=')
                    state = 5;
                else if (*forward is '>')
                    state = 6;
                break;
            case 1:
                if (*forward is '=')
                    state = 2;
                else if (*forward is '>')
                    state = 3;
                else
                    state = 4;
                break;
            case 5:
                if (*forward is '=')
                    state = 9;
                else {
                    state = 10;
                    token->type = TOKEN_ASSIGN;
                    token->name = (char *) ASSIGN;
                }
                break;
            case 6:
                if (*forward is '=')
                    state = 7;
                else
                    state = 8;
                break;
            case 2:
                state = 10;
                token->type = TOKEN_RELOP_LE;
                token->name = (char *) RELOP_LE;
                break;
            case 3:
                state = 10;
                token->type = TOKEN_RELOP_NE;
                token->name = (char *) RELOP_NE;
                break;
            case 4:
                state = 10;
                token->type = TOKEN_RELOP_LT;
                token->name = (char *) RELOP_LT;
                break;
            case 9:
                state = 10;
                token->type = TOKEN_RELOP_EQ;
                token->name = (char *) RELOP_EQ;
                break;
            case 7:
                state = 10;
                token->type = TOKEN_RELOP_GE;
                token->name = (char *) RELOP_GE;
                break;
            case 8:
                state = 10;
                token->type = TOKEN_RELOP_GT;
                token->name = (char *) RELOP_GT;
                break;
            default:
                break;
        }
        if (state is 10) {
            __backward();
            break;
        }
        __forward();
    }
}

short get_next_token(struct Token *token) {
    forward = lexeme_begin;
    if (letter)
        id_and_keyword_token(token);
    else if (digit)
        number_token(token);
    else if (*forward is '>' or *forward is '=' or *forward is '<')
        relop_token(token);
    else if (blank or space)
        blank_token(token);
    else
        fail();
    lexeme_begin = forward + 1;
    return HAVE_TOKEN;
}

