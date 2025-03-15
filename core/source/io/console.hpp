#pragma once

#include "string/format.hpp"
#include "string/string_ref.hpp"

#include <cstdio>

namespace pulsar {

inline void Printf(const StringRef format, auto&&... args) {
    ::printf("%s", VFormat(format, args...).c_str());
}

inline void PrintLine(const StringRef message) {
    Printf("%s\n", message.Data());
}

inline void Print(const StringRef message) {
    Printf("%s", message.Data());
}

}  // namespace pulsar
