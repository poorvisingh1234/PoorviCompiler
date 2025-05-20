cmake_minimum_required(VERSION 3.15)
project(PoorviCompiler)

set(CMAKE_CXX_STANDARD 17)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(PoorviCompiler ${SOURCES})

llvm_map_components_to_libnames(llvm_libs
    core support nativecodegen passes orcjit
)

target_link_libraries(PoorviCompiler ${llvm_libs})
