#pragma once

#include "io/file_handle.hpp"
#include "string/string_ref.hpp"

namespace pulsar {

class PlatformFileHandle : public FileHandle {
public:
    bool Close();

    virtual s64 Tell() override;

    virtual bool Seek(s64 position) override;

    virtual bool Read(u8* destination, size_t nbytes) override;

    virtual bool Write(const u8* source, size_t nbytes) override;

    virtual bool Flush() override;

    virtual size_t Size() override;

    explicit PlatformFileHandle(FILE* stream);

    virtual ~PlatformFileHandle() override;

private:
    FILE* stream_;
    s32 position_;
};

}  // namespace pulsar