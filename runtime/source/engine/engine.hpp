#pragma once

#include "runtime_exports.hpp"

namespace pulsar {

/**
 * @class Engine
 * @brief The Engine class provides functionalities for initializing,
 * running, and shutting down the engine.
 *
 * The Engine class is designed as a singleton, ensuring that only one
 * instance of the engine exists throughout the application. It provides
 * methods to initialize the engine, check its running status, and shut it
 * down properly.
 */
class PULSAR_RUNTIME_API Engine {
public:
    static Engine& Get();

    /**
     * @brief Initializes the engine.
     *
     * This function sets up all necessary components and resources
     * required for the engine to run. It should be called before
     * any other engine functions are used.
     *
     * @return true if initialization is successful, false otherwise.
     */
    bool Init();

    /**
     * @brief Shuts down the engine, performing any necessary cleanup.
     *
     * @return true if the shutdown was successful, false otherwise.
     */
    bool Shutdown();

    /**
     * @brief Checks if the engine is currently running.
     *
     * @return true if the engine is running, false otherwise.
     */
    bool IsRunning() const;

    /**
     * @brief Updates the state of the engine for the current frame.
     * 
     * This function should be called once per frame to advance the engine's
     * state, process input, update game logic, and perform any other per-frame
     * operations.
     */
    void Tick();

public:
    Engine() = default;
    ~Engine() = default;

private:
    bool running_ = true;
};

}  //namespace pulsar