#include "lexer.h"
#include <iostream>
#include <lexer.h>


namespace Lex {

    void const initiation(std::basic_streambuf<char_t> *stream) {

        // set up the sentry of buffer
        *BUFFER_M_PTR = EOF;
        *BUFFER_R_PTR = EOF;

        __in.rdbuf(stream);
        __load_stream(BUFFER_LEFT);

        // load key word
        KEYS.insert("if", Symbol_Info{
                TOKEN_KEY
        });
        KEYS.insert("else", Symbol_Info{
                TOKEN_KEY
        });
        KEYS.insert("while", Symbol_Info{
                TOKEN_KEY
        });
        KEYS.insert("elseif", Symbol_Info{
                TOKEN_KEY
        });
        KEYS.insert("do", Symbol_Info{
                TOKEN_KEY
        });
        KEYS.insert("for", Symbol_Info{
                TOKEN_KEY
        });
        KEYS.insert("void", Symbol_Info{
                TOKEN_KEY
        });
        KEYS.insert("int", Symbol_Info{
                TOKEN_KEY
        });
        KEYS.insert("double", Symbol_Info{
                TOKEN_KEY
        });
        KEYS.insert("char", Symbol_Info{
                TOKEN_KEY
        });
        KEYS.insert("return", Symbol_Info{
                TOKEN_KEY
        });
    }

    void __load_data_from_input(char_t *dest, unsigned int len) {
        char_t c;
        for (unsigned int i = 0; i < len; i++) {
            c = static_cast<char_t >(__in.get());
            *dest++ = c;
            if (c == EOF)
                break;
        }
    }

    void __load_stream(int_t which_buffer) {
        switch (which_buffer) {
            case BUFFER_LEFT:
                __load_data_from_input(BUFFER_L_PTR, MAX_BUFFER_SIZE);
                break;
            case BUFFER_RIGHT:
                __load_data_from_input(BUFFER_M_PTR + 1, MAX_BUFFER_SIZE);
                break;
            default:
                break;
        }
    }

    void __forward() {
        BUFFER_POSITION++;
        if (current_character == NEWLINE) {
            BUFFER_LINE++;
            BUFFER_POSITION = 1;
        }

        switch (next_character) {
            case EOF:
                if (forward == BUFFER_M_PTR) {
                    __load_stream(BUFFER_RIGHT);
                    ++forward;
                } else if (forward == BUFFER_R_PTR) {
                    __load_stream(BUFFER_LEFT);
                    forward = BUFFER_L_PTR;
                } else {
                    // handled all text
                    FINISH = 1;
                    __in.clear();
                }
            default:
                break;
        }
    }

    bool_t __blank() {
        return isblank(current_character);
    }

    bool_t __space() {
        return isspace(current_character);
    }

    bool_t __brace() {
        return current_character == '{' || current_character == '}';
    }

    bool_t __brackets() {
        return current_character == '(' || current_character == ')';
    }

    bool_t __letter() {
        return isalpha(current_character) || current_character == '_';
    }

    bool_t __number() {
        return isdigit(current_character);
    }

    bool_t __m_brackets() {
        return current_character == '[' || current_character == ']';
    }

    bool_t __relop() {
        return current_character == '>' ||
               current_character == '=' ||
               current_character == '<';
    }

    bool_t __quotation() {
        return current_character == '"';
    }

    bool_t __arithmetic() {
        return current_character == '+' ||
               current_character == '-' ||
               current_character == '/' ||
               current_character == '*';
    }

    void Lexer::fail() {
        std::cout << "Lexer occurred error at " << "line " << BUFFER_LINE << ", position " << BUFFER_POSITION << " !"
                  << "\n";
        exit(1);
    }

    struct Token Lexer::id_or_key() {
        int_t state = 0; // state of start
        Token token;
        while (true) {
            switch (state) {
                case 0:
                    if (letter) {
                        state = 1;
                    } else
                        fail();
                    break;
                case 1:
                    if (letter or number) {
                        state = 1;
                    } else
                        state = 2;
                default:
                    break;
            }
            if (state == 2) {
                if (KEYS.have(token.name))
                    token.type = TOKEN_KEY;
                else
                    token.type = TOKEN_ID;

                break;
            }
            token.name += current_character;
            __forward();
        }
        return token;
    }


    struct Token Lexer::digit() {
        int_t state = 0;
        Token token;

        while (true) {
            switch (state) {
                case 0:
                    if (number)
                        state = 1;
                    else
                        fail();
                    break;
                case 1:
                    if (number)
                        state = 1;
                    else if (current_character == '.')
                        state = 2;
                    else if (current_character == 'E' or current_character == 'e')
                        state = 4;
                    else
                        state = 8;
                    break;
                case 2:
                    if (number)
                        state = 3;
                    else
                        fail();
                    break;
                case 3:
                    if (number)
                        state = 3;
                    else if (current_character == 'E' || current_character == 'e')
                        state = 4;
                    else
                        state = 9;
                    break;
                case 4:
                    if (current_character == '+' || current_character == '-')
                        state = 5;
                    else if (number)
                        state = 6;
                    else
                        fail();
                    break;
                case 5:
                    if (number)
                        state = 6;
                    else
                        fail();
                    break;
                case 6:
                    if (number)
                        state = 6;
                    else
                        state = 7;
                    break;
                default:
                    break;
            }

            if (state == 7) {
                token.type = TOKEN_NUMBER_R;
                break;
            }

            if (state == 8) {
                token.type = TOKEN_NUMBER_Z;
                break;
            }

            if (state == 9) {
                token.type = TOKEN_NUMBER_R;
                break;
            }
            token.name += current_character;
            __forward();
        }
        return token;
    }

    struct Token Lexer::comparison_or_assign() {
        int_t state = 0;
        Token token;

        while (true) {
            switch (state) {
                case 0:
                    if (current_character == '<')
                        state = 1;
                    else if (current_character == '=')
                        state = 5;
                    else if (current_character == '>')
                        state = 6;
                    else
                        fail();
                    break;
                case 1:
                    if (current_character == '=')
                        state = 2;
                    else if (current_character == '>')
                        state = 3;
                    else
                        state = 4;
                    break;
                case 5:
                    if (current_character == '=')
                        state = 9;
                    else
                        state = 10;
                    break;
                case 6:
                    if (current_character == '=')
                        state = 7;
                    else
                        state = 8;
                    break;
                default:
                    break;
            }

            token.name += current_character;
            __forward();
            if (state == 9) {
                token.type = TOKEN_RELOP_EQ;
                break;
            }

            if (state == 10) {
                token.type = TOKEN_ASSIGN;
                break;
            }

            if (state == 2) {
                token.type = TOKEN_RELOP_LE;
                break;
            }

            if (state == 3) {
                token.type = TOKEN_RELOP_NE;
                break;
            }

            if (state == 4) {
                token.type = TOKEN_RELOP_LT;
                break;
            }

            if (state == 7) {
                token.type = TOKEN_RELOP_GE;
                break;
            }

            if (state == 8) {
                token.type = TOKEN_RELOP_GT;
                break;
            }
        }
        return token;
    }

    struct Token Lexer::blank_or_space() {
        int_t state = 0;
        Token token;
        while (true) {
            switch (state) {
                case 0:
                    if (blank or space)
                        state = 1;
                    else
                        fail();
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
            if (state == 2) {
                token.type = TOKEN_BLANK;
                break;
            }
            token.name += current_character;
            __forward();
        }
        return token;
    }

    struct Token Lexer::braces_or_brackets() {
        Token token;
        if (m_brackets or brackets or brace) {
            token.name += current_character;

            if (m_brackets)
                token.type = TOKEN_M_BRACKETS;
            else if (brackets)
                token.type = TOKEN_BRACKETS;
            else
                token.type = TOKEN_BRACE;
        } else
            fail();
        __forward();
        return token;
    }

    struct Token Lexer::str() {
        int state = 0;
        Token token;

        while (true) {
            switch (state) {
                case 0:
                    if (quotation)
                        state = 1;
                    else
                        fail();
                    break;
                case 1:
                    if (quotation)
                        state = 2;
                    else
                        state = 1;
                    break;
                default:
                    break;
            }
            if (!quotation)
                token.name += current_character;
            if (state == 2) {
                __forward();
                token.type = TOKEN_STR;
                break;
            }
            __forward();
        }
        return token;
    }

    struct Token Lexer::arithmetic_t() {
        Token token;
        token.name += current_character;
        token.type = TOKEN_ARITHMETIC;
        __forward();
        return token;
    }

    struct Token Lexer::next_token() {
        Token token;

        if (letter)
            token = id_or_key();
        else if (number)
            token = digit();
        else if (relop)
            token = comparison_or_assign();
        else if (blank or space)
            token = blank_or_space();
        else if (brackets or m_brackets or brace)
            token = braces_or_brackets();
        else if (quotation)
            token = str();
        else if (arithmetic)
            token = arithmetic_t();
        else
            fail();

        lexeme_begin = forward;
        return token;
    }


    void Symbols::insert(std::string id, struct Symbol_Info info) {
        table[id] = info;
    }

    bool_t Symbols::have(std::string id) {
        return table.count(id) > 0;
    }
}
