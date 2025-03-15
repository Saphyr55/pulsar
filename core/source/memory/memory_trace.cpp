#include "memory_trace.hpp"

namespace pulsar {

void MemoryTrace::GlobalAddFreedBytes(u64 size) {
    Get().AddFreedBytes(size);
}

void MemoryTrace::GlobalAddAllocateBytes(u64 size) {
    Get().AddAllocateBytes(size);
}

size_t MemoryTrace::GetGlobalMemoryUsage() {
    return Get().GetMemoryUsage();
}

MemoryTrace& MemoryTrace::Get() {
    static MemoryTrace tracer;
    return tracer;
}

void MemoryTrace::AddFreedBytes(u64 size) {
    memory_usage_ -= size;
}

void MemoryTrace::AddAllocateBytes(u64 size) {
    memory_usage_ += size;
}

size_t MemoryTrace::GetMemoryUsage() const {
    return memory_usage_;
}

}  //namespace pulsar