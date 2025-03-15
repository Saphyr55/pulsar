#include "main/main.hpp"
#include "engine/engine.hpp"

#include <cstdlib>

using namespace pulsar;

int32_t PulsarMain(int32_t argc, const char** argv) {
    Engine::Get().Init();
    
    while (Engine::Get().IsRunning()) {
        Engine::Get().Tick();
    }

    Engine::Get().Shutdown();

    return EXIT_SUCCESS;
}
