#pragma once

#include "string/string_ref.hpp"
#include "string/string.hpp"

namespace pulsar {

template <typename... Args>
inline StringRef VFormat(StringRef format, Args... args) {
    
    int size = snprintf(nullptr, 0, format.Data(), args...);
    if (size < 0) {
        return StringRef("");
    }

    String buffer(size + 1);
    snprintf(buffer.Data(), size + 1, format.Data(), args...);

    return StringRef(buffer.Data());
}

}
