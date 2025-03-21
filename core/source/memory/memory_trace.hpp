#pragma once

#include "core_exports.hpp"
#include "defines.hpp"

namespace pulsar {

class PULSAR_CORE_API MemoryTrace {
public:

    static void GlobalAddFreedBytes(u64 size);

    static void GlobalAddAllocateBytes(u64 size);

    static size_t GetGlobalMemoryUsage();

private:

    static MemoryTrace& Get();

    void AddFreedBytes(u64 size);
    void AddAllocateBytes(u64 size);
    size_t GetMemoryUsage() const;

private:
    u64 memory_usage_;
};



}  //namespace pulsar