#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include <iostream>
#include <fstream>

int main() {
    std::ifstream fin("test.txt");
    Lex::initiation(fin.rdbuf());
    Lex::Lexer lexer;
    while (!Lex::FINISH) {
        Lex::Token token = lexer.next_token();
        if (token.type != 11)
            std::cout << "Token: " << token.type << "\nvalue: " << token.name << std::endl;
    }
    return 0;
}