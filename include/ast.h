#pragma once
#include <string>
#include <vector>
#include <memory>

struct Expr;
struct Stmt;
using ExprPtr = std::shared_ptr<Expr>;
using StmtPtr = std::shared_ptr<Stmt>;

struct Expr {
    virtual ~Expr() = default;
};

struct NumberExpr : Expr {
    int value;
    NumberExpr(int val) : value(val) {}
};

struct VarExpr : Expr {
    std::string name;
    VarExpr(const std::string& n) : name(n) {}
};

struct AssignExpr : Expr {
    std::string name;
    ExprPtr value;
    AssignExpr(const std::string& n, ExprPtr v) : name(n), value(v) {}
};

struct Stmt {
    virtual ~Stmt() = default;
};

struct ReturnStmt : Stmt {
    ExprPtr expr;
    ReturnStmt(ExprPtr e) : expr(e) {}
};

struct VarDecl : Stmt {
    std::string name;
    ExprPtr init;
    bool isGlobal;
    VarDecl(const std::string& n, ExprPtr i, bool g) : name(n), init(i), isGlobal(g) {}
};

struct Block : Stmt {
    std::vector<StmtPtr> statements;
};

struct Function : Stmt {
    std::string name;
    Block body;
    Function(const std::string& n, Block b) : name(n), body(b) {}
};
