#pragma once
#include "lexer.h"
#include "ast.h"
#include <vector>

StmtPtr parse(const std::vector<Token>& tokens);
