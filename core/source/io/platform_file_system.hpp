#pragma once

#include "io/file_system.hpp"

namespace pulsar {  

class PlatformFileSystem : public FileSystem {
public:
    virtual bool FileExists(StringRef filepath) const override;

    virtual void MakeDirectory(StringRef path) override;

    virtual void RemoveFile(StringRef filepath) override;

    virtual void Rename(StringRef path, StringRef new_name) override;

    virtual void Move(StringRef subject, StringRef toPath) override;

    virtual FileOpenError<SharedRef<FileHandle>> OpenWrite(
        StringRef filepath) const override;

    virtual FileOpenError<SharedRef<FileHandle>> OpenRead(
        StringRef filepath) const override;

public:
    virtual ~PlatformFileSystem() override;
};

}  // namespace pulsar