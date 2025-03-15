#include "io/platform_file_system.hpp"
#include "io/platform_file_handle.hpp"
#include "string/string_ref.hpp"

#include <stdio.h>
#include <sys/stat.h>

namespace pulsar {

FileSystem& FileSystem::GetPlatformFileSystem() {
    static PlatformFileSystem platfomFileSystem;
    return platfomFileSystem;
}

bool PlatformFileSystem::FileExists(StringRef filepath) const {
#ifdef _MSC_VER
    struct _stat buffer {};

    return _stat(filepath, &buffer) == 0;
#else
    stat buffer{};
    return stat(filepath, &buffer) == 0;
#endif
}

void PlatformFileSystem::MakeDirectory(StringRef path) {}

void PlatformFileSystem::RemoveFile(StringRef filepath) {}

void PlatformFileSystem::Rename(StringRef path, StringRef new_name) {}

void PlatformFileSystem::Move(StringRef subject, StringRef to_path) {}

FileOpenError<SharedRef<FileHandle>> PlatformFileSystem::OpenWrite(
    StringRef filepath) const {
    using FileOpenErrorType = FileOpenError<SharedRef<FileHandle>>;

    FILE* stream;
    errno_t error = fopen_s(&stream, filepath, "wb");

    if (!stream) {
        return FileOpenErrorType::Failure(FileSystemOpenError::UNKNOWN);
    }

    SharedRef<FileHandle> file = MakeSharedRef<PlatformFileHandle>(stream);

    return FileOpenErrorType::Success(file);
}

FileOpenError<SharedRef<FileHandle>> PlatformFileSystem::OpenRead(
    StringRef filepath) const {
    using FileOpenErrorType = FileOpenError<SharedRef<FileHandle>>;
    
    FILE* stream;
    errno_t error = fopen_s(&stream, filepath, "rb");

    if (!stream) {
        return FileOpenErrorType::Failure(FileSystemOpenError::UNKNOWN);
    }

    SharedRef<FileHandle> file = MakeSharedRef<PlatformFileHandle>(stream);

    return FileOpenErrorType::Success(file);
}

PlatformFileSystem::~PlatformFileSystem() {}

}  // namespace pulsar