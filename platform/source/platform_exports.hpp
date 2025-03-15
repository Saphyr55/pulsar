#pragma once

#ifdef PULSAR_PLATFORM_MODULE

#ifdef PULSAR_PLATFORM_EXPORTS
#ifdef _MSC_VER
#define PULSAR_PLATFORM_API __declspec(dllexport)
#else
#define PULSAR_PLATFORM_API __attribute__((visibility("default")))
#endif
#else
#ifdef _MSC_VER
#define PULSAR_PLATFORM_API __declspec(dllimport)
#else
#define PULSAR_PLATFORM_API
#endif
#endif

#else

#define PULSAR_PLATFORM_API

#endif