#pragma once

namespace pulsar {

class Engine {
public:
    static Engine& Get();

    bool Init();
    
    bool Shutdown();
};

}  //namespace pulsar