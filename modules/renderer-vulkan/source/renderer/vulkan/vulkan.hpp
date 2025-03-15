#pragma once

#include <vulkan/vulkan.h>
#include "module/module.hpp"
#include "module/module_registry.hpp"
#include "object/object.hpp"
#include "renderer_vulkan_exports.hpp"

namespace pulsar {

class VulkanObject;

class PULSAR_RENDERER_VULKAN_API VulkanModule : public Module {
public:
    VulkanModule() = default;
    ~VulkanModule() = default;

    void Startup();
    void Shutdown();

private:
    VulkanObject* object_;
};

class PULSAR_RENDERER_VULKAN_API VulkanObject : public Object {
public:
    friend class VulkanModule;

    VulkanObject() = default;
    ~VulkanObject() = default;

    virtual void Tick() override;

private:
    VkInstance instance_;
    VkPhysicalDevice physical_device_;
    VkDevice device_;
#ifdef _WIN32
    VkSurfaceKHR surface_;
#endif
    VkCommandPool command_pool_;
    VkCommandBuffer command_buffer_;
    uint32_t queue_family_index_;
    uint32_t queue_family_count_;
};

PULSAR_ADD_MODULE("VulkanModule", VulkanModule)

}  //namespace pulsar
