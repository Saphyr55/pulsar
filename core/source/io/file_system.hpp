#pragma once

#include "collection/result.hpp"
#include "core_exports.hpp"
#include "defines.hpp"
#include "memory/shared_ref.hpp"
#include "string/string_ref.hpp"

namespace pulsar {

class FileHandle;

enum class FileSystemOpenError : u8 {
    UNKNOWN
};

template <typename T>
using FileOpenError = Result<T, FileSystemOpenError>;

class PULSAR_CORE_API FileSystem {
public:
    static FileSystem& GetPlatformFileSystem();

    virtual bool FileExists(StringRef filepath) const = 0;

    virtual void MakeDirectory(StringRef path) = 0;

    virtual void RemoveFile(StringRef filepath) = 0;

    virtual void Rename(StringRef path, StringRef new_name) = 0;

    virtual void Move(StringRef subject, StringRef toPath) = 0;

    virtual FileOpenError<SharedRef<FileHandle>> OpenWrite(
        StringRef filepath) const = 0;

    virtual FileOpenError<SharedRef<FileHandle>> OpenRead(
        StringRef filepath) const = 0;

public:
    virtual ~FileSystem() = default;
};

}  // namespace pulsar