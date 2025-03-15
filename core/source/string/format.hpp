#pragma once

#include "string/string_ref.hpp"
#include "string/string_buffer.hpp"

namespace pulsar {

template <typename... Args>
inline String VFormat(StringRef format, Args... args) {
    
    int size = snprintf(nullptr, 0, format.Data(), args...);
    if (size < 0) {
        return String("");
    }

    StringBuffer buffer(size + 1);
    snprintf(buffer.Data(), size + 1, format.Data(), args...);

    return String(buffer.Data());
}

}
