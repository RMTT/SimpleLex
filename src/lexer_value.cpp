#include "lexer.h"

namespace Lex {
    char_t BUFFER[REAL_BUFFER_SIZE];
    int_t BUFFER_LINE = 1;
    int_t BUFFER_POSITION = 1;

    std::istream __in(nullptr);

    char *forward = BUFFER_L_PTR;
    char *lexeme_begin = BUFFER_L_PTR;

    Symbols KEYS;

    bool_t FINISH = 0;
}
