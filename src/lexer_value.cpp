#include "lexer.h"

namespace Lex {
    Symbols KEYS;

    char_t BUFFER[REAL_BUFFER_SIZE];

    int_t BUFFER_LINE = 1;
    int_t BUFFER_POSITION = 1;

    char_t *forward = BUFFER;
    char_t *lexeme_begin = BUFFER;

    std::istream __in(nullptr);

    bool_t FINISH = 0;
}
