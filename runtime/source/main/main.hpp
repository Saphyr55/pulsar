#pragma once

#include <cstdlib>
#include "defines.hpp"
#include "runtime_exports.hpp"
#include "io/console.hpp"

namespace pulsar {

    int32_t PULSAR_RUNTIME_API PulsarMain(int32_t argc, const char** argv);
    
}

int32_t PULSAR_RUNTIME_API main(int32_t argc, const char** argv);


