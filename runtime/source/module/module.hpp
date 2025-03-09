#pragma once

namespace pulsar {

class Module {
public:
    virtual void Startup() {}
    
    virtual void Shutdown() {}

    virtual ~Module() {}
};

}  //namespace pulsar

