#pragma once
#include <string>
#include <vector>

enum class TokenType {
    Int, Return, Identifier, Number, Assign,
    LParen, RParen, LBrace, RBrace, Semicolon, Eof
};

struct Token {
    TokenType type;
    std::string lexeme;
};

std::vector<Token> lex(const std::string& input);
