#include "lexer.h"
#include <cctype>

std::vector<Token> lex(const std::string& input) {
    std::vector<Token> tokens;
    size_t i = 0;

    auto isAlpha = [](char c) { return std::isalpha(c) || c == '_'; };
    auto isDigit = [](char c) { return std::isdigit(c); };

    while (i < input.size()) {
        if (std::isspace(input[i])) {
            ++i;
        } else if (input.substr(i, 6) == "return") {
            tokens.push_back({TokenType::Return, "return"});
            i += 6;
        } else if (input.substr(i, 3) == "int") {
            tokens.push_back({TokenType::Int, "int"});
            i += 3;
        } else if (isAlpha(input[i])) {
            std::string id;
            while (i < input.size() && (isAlpha(input[i]) || isDigit(input[i])))
                id += input[i++];
            tokens.push_back({TokenType::Identifier, id});
        } else if (isDigit(input[i])) {
            std::string num;
            while (i < input.size() && isDigit(input[i]))
                num += input[i++];
            tokens.push_back({TokenType::Number, num});
        } else {
            switch (input[i]) {
                case '=': tokens.push_back({TokenType::Assign, "="}); break;
                case '(': tokens.push_back({TokenType::LParen, "("}); break;
                case ')': tokens.push_back({TokenType::RParen, ")"}); break;
                case '{': tokens.push_back({TokenType::LBrace, "{"}); break;
                case '}': tokens.push_back({TokenType::RBrace, "}"}); break;
                case ';': tokens.push_back({TokenType::Semicolon, ";"}); break;
            }
            ++i;
        }
    }

    tokens.push_back({TokenType::Eof, ""});
    return tokens;
}

