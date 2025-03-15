#pragma once

#ifdef PULSAR_RUNTIME_MODULE

#ifdef PULSAR_RUNTIME_EXPORTS
#ifdef _MSC_VER
#define PULSAR_RUNTIME_API __declspec(dllexport)
#else
#define PULSAR_RUNTIME_API __attribute__((visibility("default")))
#endif
#else
#ifdef _MSC_VER
#define PULSAR_RUNTIME_API __declspec(dllimport)
#else
#define PULSAR_RUNTIME_API 
#endif
#endif

#else

#define PULSAR_RUNTIME_API 

#endif