#pragma once

#ifdef PULSAR_RENDERER_VULKAN_MODULE

#ifdef PULSAR_RENDERER_VULKAN_EXPORTS
#ifdef _MSC_VER
#define PULSAR_RENDERER_VULKAN_API __declspec(dllexport)
#else
#define PULSAR_RENDERER_VULKAN_API __attribute__((visibility("default")))
#endif
#else
#ifdef _MSC_VER
#define PULSAR_RENDERER_VULKAN_API /* __declspec(dllimport) */
#else
#define PULSAR_RENDERER_VULKAN_API 
#endif
#endif

#else

#define PULSAR_RENDERER_VULKAN_API 

#endif