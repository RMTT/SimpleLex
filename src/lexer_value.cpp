#include "lexer.h"

namespace Lex {
    char_t BUFFER[REAL_BUFFER_SIZE];
    int_t BUFFER_LINE = 1;
    int_t BUFFER_POSITION = 1;

    std::istream __in(nullptr);

    char *forward = BUFFER;
    char *lexeme_begin = BUFFER;

    Symbols KEYS;

    bool_t FINISH = 0;
}
