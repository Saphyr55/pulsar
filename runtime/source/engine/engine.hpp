#pragma once

namespace pulsar {

class Engine {
public:
    static Engine& Get();

    bool Run();

    bool Shutdown();

    bool Startup();
};

}  //namespace pulsar