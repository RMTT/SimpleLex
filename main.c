#include <stdio.h>
#include "lexer.h"

int main() {
    freopen("test.txt", "r", stdin);
    lexer_init();
    while (FINISH == 0) {
        struct Token *token = malloc(sizeof(struct Token));
        get_next_token(token);
        if (token->type != TOKEN_BLANK and token->name != NULL)
            printf("%s\n", token->name);
    }
    return 0;
}