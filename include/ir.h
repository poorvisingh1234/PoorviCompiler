#pragma once

#include "ast.h"
#include <memory>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

std::unique_ptr<llvm::Module> generateIR(const std::vector<StmtPtr>& stmts);

