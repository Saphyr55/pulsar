#include "main/main.hpp"
#include "engine/engine.hpp"
#include "runtime_exports.hpp"

namespace pulsar {

    int32_t PulsarMain(int32_t argc, const char** argv) {

        Engine::Get().Startup();
        Engine::Get().Run();
        Engine::Get().Shutdown();

        return EXIT_SUCCESS;
    }

}