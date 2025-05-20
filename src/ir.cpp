#include "ir.h"
#include <llvm/IR/Verifier.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>

std::unique_ptr<llvm::LLVMContext> context;
std::unique_ptr<llvm::IRBuilder<>> builder;
std::unique_ptr<llvm::Module> module;

llvm::Value* codegen(const StmtPtr& stmt);

void optimizeModule(std::unique_ptr<llvm::Module>& module) {
    llvm::legacy::PassManager pm;
    pm.add(llvm::createPromoteMemoryToRegisterPass());
    pm.add(llvm::createInstructionCombiningPass());
    pm.add(llvm::createReassociatePass());
    pm.add(llvm::createGVNPass());
    pm.add(llvm::createCFGSimplificationPass());
    pm.run(*module);
}

std::unique_ptr<llvm::Module> generateIR(const std::vector<StmtPtr>& stmts) {
    context = std::make_unique<llvm::LLVMContext>();
    builder = std::make_unique<llvm::IRBuilder<>>(*context);
    module = std::make_unique<llvm::Module>("PoorviModule", *context);

    for (const auto& stmt : stmts) {
        codegen(stmt);
    }

    optimizeModule(module);

    return std::move(module);
}
