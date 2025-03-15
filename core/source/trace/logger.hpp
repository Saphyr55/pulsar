#pragma once

#include <cstdint>
#include <functional>
#include "collection/array.hpp"
#include "core_exports.hpp"

namespace pulsar {

/**
 * @enum LogSeverity
 * @brief Defines the severity levels for log messages.
 */
enum class LogSeverity : uint8_t {
    INFO = 0,
    WARN = 1,
    DEBUG = 2,
    ERROR = 3,
    FATAL = 4,
};

/**
 * @struct LogMessage
 * @brief Represents a log message with associated metadata.
 */
struct PULSAR_CORE_API LogMessage {
public:
    /** Severity level of the log message. */
    LogSeverity severity = LogSeverity::ERROR;
    /** Channel or category of the log message. */
    const char* channel = "UNKNOWN";
    /** The actual log message. */
    const char* message = "NO MESSAGE";
    /** Line number where the log message was generated. */
    uint32_t line = UINT32_MAX;
    /** Function name where the log message was generated. */
    const char* function = "GLOBAL";
    /** File name where the log message was generated. */
    const char* file = "GLOBAL";
    /** Flag indicating whether the log message is verbose. */
    bool verbose = false;

public:
    LogMessage() = default;

    LogMessage(LogSeverity severity,
               const char* channel,
               const char* message,
               uint32_t line,
               const char* function,
               const char* file,
               bool verbose)
        : severity(severity)
        , channel(channel)
        , message(message)
        , line(line)
        , function(function)
        , file(file)
        , verbose(verbose) {}

    ~LogMessage() = default;
};

/**
 * @typedef LogFn
 * @brief Function type for logging callbacks.
 */
using LogFn = std::function<void(const LogMessage& message)>;

/**
 * @class Logger
 * @brief Provides a logging interface with a delegate function.
 */
class PULSAR_CORE_API Logger {
public:
    /**
     * @brief Gets the default logger instance.
     * @return Reference to the default logger.
     */
    static Logger& GetDefault();

    /**
     * @brief Logs a message using the registered delegate.
     * @param message The log message to be logged.
     */
    void Log(const LogMessage& message) const;

    /**
     * @brief Gets the current logging delegate.
     * @return The current logging function.
     */
    LogFn GetDelegate() const;

    /**
     * @brief Sets the logging delegate.
     * @param func The logging function to set as the delegate.
     */
    void SetDelegate(LogFn func);

    /**
     * @brief Constructs a Logger with a specified logging function.
     * @param fn The logging function to use as the delegate.
     */
    Logger(LogFn fn);

    /**
     * @brief Destructor.
     */
    ~Logger() = default;

private:
    LogFn log_fn_;  ///< The logging delegate function.
};

/**
 * @class ConsoleLogger
 * @brief Provides a logger that outputs messages to the console.
 */
class PULSAR_CORE_API ConsoleLogger {
public:
    /**
     * @brief Gets the logging delegate for console output.
     * @return The logging function for console output.
     */
    LogFn GetDelegate();

    /**
     * @brief Constructs a ConsoleLogger.
     */
    ConsoleLogger();

    /**
     * @brief Destructor.
     */
    ~ConsoleLogger() = default;

private:
    LogFn console_log_fn_; /** The logging function for console output.  */
};

/**
 * @class CompositeLogger
 * @brief Combines multiple loggers into a single logger.
 */
class PULSAR_CORE_API CompositeLogger {
public:
    /**
     * @brief Adds a logging function to the composite logger.
     * @param logger The logging function to add.
     */
    void AddLogrFn(LogFn logger);

    /**
     * @brief Logs a message using all registered logging functions.
     * @param message The log message to be logged.
     */
    void Log(const LogMessage& message) const;

private:
    Array<LogFn> loggers_; /** Collection of registered logging functions. */
};
}  //namespace pulsar