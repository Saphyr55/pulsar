#ifdef _WIN32

#include "defines.hpp"
#include "platform_exports.hpp"
#include "main/main.hpp"

#include <Windows.h>

#include <stdio.h>

int32_t main(int32_t argc, const char** argv) {
    printf("Hello\n");
    return 0;
}

#endif