#pragma once

#include "memory/shared_ref.hpp"
#include "string/string_ref.hpp"

namespace pulsar {

class PULSAR_CORE_API FileHandle {
public:
    virtual s64 Tell() = 0;

    virtual bool Seek(s64 position) = 0;

    virtual bool Read(u8* destination, size_t nbytes) = 0;

    virtual bool Write(const u8* source, size_t nbytes) = 0;

    virtual bool Flush() = 0;

    virtual size_t Size() = 0;

    virtual ~FileHandle() = default;
};

}  // namespace pulsar