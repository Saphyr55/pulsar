#include "logger.hpp"  // Assuming the header is named logger.hpp
#include <iostream>

namespace pulsar {

Logger& Logger::GetDefault() {
    static Logger logger = [&]() {
        static ConsoleLogger console_logger;
        static CompositeLogger compiste_logger;
        compiste_logger.AddLogrFn(console_logger.GetDelegate());
        return Logger([&](const LogMessage& message) {
            compiste_logger.Log(message);
        });
    }();
    return logger;
}

void Logger::Log(const LogMessage& message) const {
    log_fn_(message);
}

LogFn Logger::GetDelegate() const {
    return log_fn_;
}

void Logger::SetDelegate(LogFn func) {
    log_fn_ = func;
}

Logger::Logger(LogFn fn)
    : log_fn_(fn) {}

ConsoleLogger::ConsoleLogger() {
    console_log_fn_ = [](const LogMessage& log_message) {
        const char* severity_str = "";
        switch (log_message.severity) {
            case LogSeverity::INFO:
                severity_str = "INFO";
                break;
            case LogSeverity::WARN:
                severity_str = "WARN";
                break;
            case LogSeverity::ERROR:
                severity_str = "ERROR";
                break;
            case LogSeverity::FATAL:
                severity_str = "FATAL";
                break;
            case LogSeverity::DEBUG:
                severity_str = "DEBUG";
                break;
            default:
                severity_str = "UNKNOWN";
                break;
        }
    
        std::cout << "[" << severity_str << "] "
                  << "[" << log_message.channel << "]"
                  << " Message: " << log_message.message << "\n";
    };
}

LogFn ConsoleLogger::GetDelegate() {
    return console_log_fn_;
}

void CompositeLogger::AddLogrFn(LogFn log_fn) {
    loggers_.Add(log_fn);
}

void CompositeLogger::Log(const LogMessage& message) const {
    for (const auto& logger : loggers_) {
        logger(message);
    }
}

}  // namespace pulsar