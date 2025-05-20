#include "parser.h"
#include <stdexcept>

static size_t current;
static std::vector<Token> toks;

static Token peek() {
    return toks[current];
}

static Token advance() {
    return toks[current++];
}

static bool match(TokenType type) {
    if (peek().type == type) {
        advance();
        return true;
    }
    return false;
}

static ExprPtr parseExpr();

static ExprPtr parsePrimary() {
    if (match(TokenType::Number)) {
        return std::make_shared<NumberExpr>(std::stoi(toks[current - 1].lexeme));
    } else if (match(TokenType::Identifier)) {
        return std::make_shared<VarExpr>(toks[current - 1].lexeme);
    }
    throw std::runtime_error("Expected expression");
}

static ExprPtr parseExpr() {
    if (peek().type == TokenType::Identifier && toks[current + 1].type == TokenType::Assign) {
        std::string name = advance().lexeme;
        advance(); // skip '='
        ExprPtr val = parseExpr();
        return std::make_shared<AssignExpr>(name, val);
    }
    return parsePrimary();
}

static StmtPtr parseStmt(bool isGlobal) {
    if (match(TokenType::Int)) {
        std::string name = advance().lexeme;
        advance(); // '='
        ExprPtr val = parseExpr();
        match(TokenType::Semicolon);
        return std::make_shared<VarDecl>(name, val, isGlobal);
    }
    if (match(TokenType::Return)) {
        ExprPtr val = parseExpr();
        match(TokenType::Semicolon);
        return std::make_shared<ReturnStmt>(val);
    }
    return nullptr;
}

StmtPtr parse(const std::vector<Token>& tokens) {
    toks = tokens;
    current = 0;
