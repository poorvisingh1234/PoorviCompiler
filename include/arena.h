#pragma once
#include <vector>
#include <cstdlib>

class Arena {
    std::vector<void*> blocks;

public:
    void* allocate(size_t size) {
        void* ptr = std::malloc(size);
        blocks.push_back(ptr);
        return ptr;
    }

    ~Arena() {
        for (void* ptr : blocks) std::free(ptr);
    }
};
