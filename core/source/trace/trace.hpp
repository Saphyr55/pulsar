#pragma once

#include "defines.hpp"
#include "trace/logger.hpp"

#define PMAKE_CONTEXT_LOG_MSG(severity, channel, msg) \
    ::pulsar::LogMessage(severity, channel, msg, __LINE__, __FUNCTION__, __FILE__, false)

#define PLOG(severity, channel, msg) \
    ::pulsar::Logger::GetDefault().Log(PMAKE_CONTEXT_LOG_MSG(severity, channel, msg));

#define PLOG_DEBUG(channel, msg) \
    PLOG(::pulsar::LogSeverity::DEBUG, channel, msg)

#define PLOG_INFO(channel, msg) \
    PLOG(::pulsar::LogSeverity::INFO, channel, msg)

#define PLOG_WARN(channel, msg) \
    PLOG(::pulsar::LogSeverity::WARN, channel, msg)

#define PLOG_ERROR(channel, msg) \
    PLOG(::pulsar::LogSeverity::ERROR, channel, msg)

#define PLOG_FATAL(channel, msg)                     \
    PLOG(::pulsar::LogSeverity::FATAL, channel, msg) \
    PDEBUGBREAK()

#define PLOG_INFO_WHEN(channel, cond, msg) \
    if (!(cond)) {                         \
        PLOG_INFO(channel, msg)            \
    }

#define PLOG_FATAL_WHEN(channel, cond, msg) \
    if (!(cond)) {                          \
        PLOG_FATAL(channel, msg)            \
    }

#define PLOG_ERROR_WHEN(channel, cond, msg) \
    if (!(cond)) {                          \
        PLOG_ERROR(channel, msg)            \
    }

#define PLOG_WARN_WHEN(channel, cond, msg) \
    if (!(cond)) {                         \
        PLOG_WARN(channel, msg)            \
    }

#define PLOG_DEBUG_WHEN(channel, cond, msg) \
    if (!(cond)) {                          \
        PLOG_DEBUG(channel, msg)            \
    }
