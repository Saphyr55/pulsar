#ifdef _WIN32

#include "main/main.hpp"

#include <Windows.h>

int32_t main(int32_t argc, const char** argv) {
    return ::pulsar::PulsarMain(argc, argv);
}

#endif