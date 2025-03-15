#include "io/platform_file_handle.hpp"

namespace pulsar {

int64_t PlatformFileHandle::Tell() {
    return ftell(stream_);
}

bool PlatformFileHandle::Seek(int64_t position) {
    if (fseek(stream_, position, SEEK_SET)) {
        position_ = position;
        return true;
    }

    return false;
}

bool PlatformFileHandle::Flush() {
    fflush(stream_);
    return true;
}

size_t PlatformFileHandle::Size() {
    return 0;
}

bool PlatformFileHandle::Write(const uint8_t* buffer, size_t nbytes) {
    if (!stream_) {
        return false;
    }

    size_t s = std::fwrite(buffer, sizeof(uint8_t), nbytes, stream_);
    if (s != nbytes) {
        return false;
    }

    return true;
}

bool PlatformFileHandle::Read(uint8_t* destination, size_t nbytes) {
    if (!destination || nbytes == 0) {
        return false;
    }

    size_t bytes_read = std::fread(destination, sizeof(uint8_t), nbytes, stream_);
    if (bytes_read != nbytes) {
        return false;
    }

    position_ += bytes_read;

    return true;
}

bool PlatformFileHandle::Close() {
    if (stream_) {
        fclose(stream_);
        stream_ = nullptr;
        return true;
    }

    return false;
}

PlatformFileHandle::PlatformFileHandle(FILE* stream)
    : stream_(stream), position_(0) {}

PlatformFileHandle::~PlatformFileHandle() {
    Close();
}

}  // namespace pulsar