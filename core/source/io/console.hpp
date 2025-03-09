#pragma once

#include "defines.hpp"
#include "core_exports.hpp"
#include "string/string_ref.hpp"

#include <cstdio>

namespace pulsar {

class PULSAR_CORE_API Console {
public:
    static inline void WriteLine(const StringRef message) { Writef("%s\n", message.Data()); }

    static inline void Write(const StringRef message) { Writef(message); }

    static inline void Writef(const StringRef format, auto&&... args) {
        printf(format, std::forward<decltype(args)>(args)...);
    }
};

}  // namespace pulsar
