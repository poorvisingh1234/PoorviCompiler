#pragma once
#include <llvm/IR/Module.h>

void emitAssembly(std::unique_ptr<llvm::Module>& module);
