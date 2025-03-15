#pragma once

#include <cstdint>
#include "core_exports.hpp"
#include "defines.hpp"

namespace pulsar {

enum class LogSeverity : uint8_t {
    INFO,
    WARN,
    ERROR,
    FATAL,
    DEBUG,
};

class PULSAR_CORE_API Logger {
public:
    void Log(LogSeverity severity, uint64_t line, const char* function, const char* file, bool verbose = false);

};

}