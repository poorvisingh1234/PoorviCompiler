#include "lexer.h"
#include "parser.h"
#include "semantic.h"
#include "ir.h"
#include "codegen.h"
#include <fstream>
#include <sstream>

int main() {
    std::ifstream file("test/test.pv");
    std::stringstream buffer;
    buffer << file.rdbuf();
    auto tokens = lex(buffer.str());
    auto ast = parse(tokens);
    analyze(ast);
    auto module = generateIR(ast);
    emitAssembly(module);
    return 0;
}
