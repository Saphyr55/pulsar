#pragma once

#include "io/file_handle.hpp"

namespace pulsar {

class PlatformFileHandle : public FileHandle {
public:
    bool Close();

    virtual int64_t Tell() override;

    virtual bool Seek(int64_t position) override;

    virtual bool Read(uint8_t* destination, size_t nbytes) override;

    virtual bool Write(const uint8_t* source, size_t nbytes) override;

    virtual bool Flush() override;

    virtual size_t Size() override;

    explicit PlatformFileHandle(FILE* stream);

    virtual ~PlatformFileHandle() override;

private:
    FILE* stream_;
    int32_t position_;
};

}  // namespace pulsar