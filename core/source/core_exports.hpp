#pragma once

#ifdef PULSAR_CORE_MODULE

#ifdef PULSAR_CORE_EXPORT

#ifdef _MSC_VER
#define PULSAR_CORE_API __declspec(dllexport)
#else
#define PULSAR_CORE_API __attribute__((visibility("default")))
#endif

#else

#ifdef _MSC_VER

#define PULSAR_CORE_API __declspec(dllimport)
#else
#define PULSAR_CORE_API
#endif

#endif

#else

#define PULSAR_CORE_API

#endif