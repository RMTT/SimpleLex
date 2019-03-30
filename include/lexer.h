#ifndef SIMPLELEX_LEXER_H
#define SIMPLELEX_LEXER_H

#include <string>
#include <iostream>
#include <fstream>
#include <map>


namespace Lex {
    typedef char char_t;
    typedef short token_type_t;
    typedef int int_t;
    typedef bool bool_t;

#define MAX_BUFFER_SIZE 2048
#define REAL_BUFFER_SIZE (2 * MAX_BUFFER_SIZE + 2)

    extern char_t BUFFER[REAL_BUFFER_SIZE];
    extern bool_t FINISH;
    extern int_t BUFFER_LINE;
    extern int_t BUFFER_POSITION;
#define BUFFER_L_PTR (BUFFER)
#define BUFFER_M_PTR (BUFFER + MAX_BUFFER_SIZE)
#define BUFFER_R_PTR (BUFFER + REAL_BUFFER_SIZE - 1)


#define TOKEN_ID 1
#define TOKEN_KEY 0
#define TOKEN_NUMBER_Z 2
#define TOKEN_NUMBER_R 12
#define TOKEN_STR 3
#define TOKEN_RELOP_LE 4
#define TOKEN_RELOP_NE 5
#define TOKEN_RELOP_LT 6
#define TOKEN_RELOP_EQ 7
#define TOKEN_RELOP_GE 8
#define TOKEN_RELOP_GT 9
#define TOKEN_ASSIGN 10
#define TOKEN_BLANK 11
#define TOKEN_BRACE 13
#define TOKEN_M_BRACKETS 14
#define TOKEN_BRACKETS 15

    struct Token {
        token_type_t type;

        std::string name;
    };

    extern char_t *forward;
    extern char_t *lexeme_begin;

#define current_character (*forward)
#define next_character (*++forward)

#define NEWLINE '\n'

    extern void __forward();

#define BUFFER_LEFT 0
#define BUFFER_RIGHT 1

    extern std::istream __in;

    extern void __load_stream(int_t which_buffer);

    class Lexer;

    class Symbols;

    extern Symbols KEYS;

    extern void const initiation(std::basic_streambuf<char_t> *);

#define letter __letter()

    extern bool_t __letter();

#define number __number()

    extern bool_t __number();

#define blank __blank()

    extern bool_t __blank();

#define space __space()

    extern bool_t __space();

#define relop __relop()

    extern bool_t __relop();

#define brace __brace()

    bool_t __brace();

#define brackets __brackets()

    bool_t __brackets();

#define m_brackets __m_brackets()

    bool_t __m_brackets();

#define quotation __quotation()

    bool_t __quotation();

    class Lexer {
    public:
        Lexer() = default;

        void fail();

        struct Token id_or_key();

        struct Token digit();

        struct Token comparison_or_assign();

        struct Token blank_or_space();

        struct Token braces_or_brackets();

        struct Token str();

        struct Token next_token();
    };

    struct Symbol_Info {
        token_type_t type;
    };

    class Symbols {
    private:
        std::map<std::string, struct Symbol_Info> table;
    public:
        Symbols() = default;

        void insert(std::string id, struct Symbol_Info);

        bool_t have(std::string id);
    };
}

#endif // SIMPLELEX_LEXER_H
