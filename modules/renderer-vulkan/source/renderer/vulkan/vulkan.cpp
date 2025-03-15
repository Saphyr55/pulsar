#include "renderer/vulkan/vulkan.hpp"
#include "defines.hpp"
#include "display/display.hpp"
#include "object/object.hpp"
#include "string/format.hpp"
#include "trace/trace.hpp"

#ifdef _WIN32
#define VK_USE_PLATFORM_WIN32_KHR 1
#include <Windows.h>
#include <vulkan/vulkan_win32.h>
#undef ERROR
#endif

namespace pulsar {


void VulkanModule::Startup() {
    PLOG_INFO("Renderer Vulkan", "Startup Vulkan renderer.");

    object_ = NewObject<VulkanObject>();
    PCHECK_MSG(object_ != nullptr, "Failed to create Vulkan object.");
    VulkanObject& object = *object_;

    // Create a Vulkan instance_.
    VkApplicationInfo app_info = {};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = "Pulsar Engine";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "Pulsar Engine";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;
    create_info.enabledLayerCount = 0;
    create_info.ppEnabledLayerNames = nullptr;
    create_info.enabledExtensionCount = 0;
    create_info.ppEnabledExtensionNames = nullptr;

    VkResult result = vkCreateInstance(&create_info, nullptr, &object.instance_);
    PLOG_FATAL_WHEN(result != VK_SUCCESS, "Renderer Vulkan", "Failed to create Vulkan instance_.");

    PLOG_INFO("Renderer Vulkan", "Successfully created Vulkan instance_.");

    // Enumerate physical devices.
    uint32_t device_count = 0;
    vkEnumeratePhysicalDevices(object.instance_, &device_count, nullptr);
    PLOG_FATAL_WHEN(device_count == 0, "Renderer Vulkan", "No Vulkan physical devices found.");

    Array<VkPhysicalDevice> devices;
    devices.Reverse(device_count);
    vkEnumeratePhysicalDevices(object.instance_, &device_count, devices.Data());
    PLOG_INFO("Renderer Vulkan", VFormat("Found %d Vulkan physical devices.", device_count));

    // Select a physical device.
    VkPhysicalDevice physical_device = VK_NULL_HANDLE;
    for (uint32_t i = 0; i < device_count; ++i) {
        VkPhysicalDevice device = devices[i];
        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(device, &properties);

        if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
            physical_device = device;
            break;
        }
    }

    PLOG_FATAL_WHEN(physical_device == VK_NULL_HANDLE, "Renderer Vulkan", "No Vulkan physical device found.");
    PLOG_INFO("Renderer Vulkan", "Selected Vulkan physical device.");

    // Create a logical device.
    float queue_priority = 1.0f;

    VkDeviceQueueCreateInfo queue_create_info = {};
    queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_create_info.queueFamilyIndex = 0;
    queue_create_info.queueCount = 1;
    queue_create_info.pQueuePriorities = &queue_priority;

    VkDeviceCreateInfo device_create_info = {};
    device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    device_create_info.queueCreateInfoCount = 1;
    device_create_info.pQueueCreateInfos = &queue_create_info;
    device_create_info.enabledLayerCount = 0;
    device_create_info.ppEnabledLayerNames = nullptr;

    const char* device_extensions[] = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    device_create_info.enabledExtensionCount = 1;
    device_create_info.ppEnabledExtensionNames = device_extensions;

    result = vkCreateDevice(physical_device, &device_create_info, nullptr, &object.device_);
    PLOG_FATAL_WHEN(result != VK_SUCCESS, "Renderer Vulkan", "Failed to create Vulkan logical device.");
    PLOG_INFO("Renderer Vulkan", "Successfully created Vulkan logical device.");

    // Create a Vulkan surface.
#ifdef _WIN32
    VkWin32SurfaceCreateInfoKHR surface_create_info = {};
    surface_create_info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    surface_create_info.hinstance = GetModuleHandle(nullptr);
    surface_create_info.hwnd = reinterpret_cast<HWND>(Display::Get().GetNativeWindowHandle(Display::MAIN_WINDOW_HANDLE));
    surface_create_info.pNext = nullptr;

    result = vkCreateWin32SurfaceKHR(object.instance_, &surface_create_info, nullptr, &object.surface_);
    PLOG_FATAL_WHEN(result != VK_SUCCESS, "Renderer Vulkan", "Failed to create Vulkan surface.");
    PLOG_INFO("Renderer Vulkan", "Successfully created Vulkan surface.");
#endif

    // Select a queue family.
    object.queue_family_count_ = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &object.queue_family_count_, nullptr);
    PLOG_FATAL_WHEN(object.queue_family_count_ == 0, "Renderer Vulkan", "No Vulkan queue families found.");
    PLOG_INFO("Renderer Vulkan", VFormat("Found %d Vulkan queue families.", object.queue_family_count_));

    Array<VkQueueFamilyProperties> queue_families(object.queue_family_count_);
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &object.queue_family_count_, queue_families.Data());

    object.queue_family_index_ = UINT32_MAX;
    for (uint32_t i = 0; i < object.queue_family_count_; ++i) {
        if (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            object.queue_family_index_ = i;
            break;
        }
    }

    PLOG_FATAL_WHEN(object.queue_family_index_ == UINT32_MAX, "Renderer Vulkan", "No Vulkan queue family found.");
    PLOG_INFO("Renderer Vulkan", "Selected Vulkan queue family.");
}

void VulkanModule::Shutdown() {
    VulkanObject& object = *object_;

    // Destroy a Vulkan command buffer.
    vkFreeCommandBuffers(object.device_, object.command_pool_, 1, &object.command_buffer_);
    PLOG_INFO("Renderer Vulkan", "Successfully freed Vulkan command buffer.");

    // Destroy a Vulkan command pool.
    vkDestroyCommandPool(object.device_, object.command_pool_, nullptr);
    PLOG_INFO("Renderer Vulkan", "Successfully destroyed Vulkan command pool.");

    // Destroy a Vulkan surface.
#ifdef _WIN32
    vkDestroySurfaceKHR(object.instance_, object.surface_, nullptr);
    PLOG_INFO("Renderer Vulkan", "Successfully destroyed Vulkan surface.");
#endif

    // Destroy a Vulkan logical device.
    vkDestroyDevice(object.device_, nullptr);
    PLOG_INFO("Renderer Vulkan", "Successfully destroyed Vulkan logical device.");

    // Destroy a Vulkan instance_.
    vkDestroyInstance(object.instance_, nullptr);
    PLOG_INFO("Renderer Vulkan", "Successfully destroyed Vulkan instance_.");

    PLOG_INFO("Renderer Vulkan", "Shutdown Vulkan renderer.");
}

void VulkanObject::Tick() {
    // Create a Vulkan command pool.
    VkCommandPoolCreateInfo command_pool_create_info = {};
    command_pool_create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    command_pool_create_info.queueFamilyIndex = queue_family_index_;
    command_pool_create_info.flags = 0;

    VkResult result = vkCreateCommandPool(device_, &command_pool_create_info, nullptr, &command_pool_);
    PLOG_FATAL_WHEN(result != VK_SUCCESS, "Renderer Vulkan", "Failed to create Vulkan command pool.");

    // Create a Vulkan command buffer.
    VkCommandBufferAllocateInfo command_buffer_allocate_info = {};
    command_buffer_allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    command_buffer_allocate_info.commandPool = command_pool_;
    command_buffer_allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    command_buffer_allocate_info.commandBufferCount = 1;

    result = vkAllocateCommandBuffers(device_, &command_buffer_allocate_info, &command_buffer_);
    PLOG_FATAL_WHEN(result != VK_SUCCESS, "Renderer Vulkan", "Failed to allocate Vulkan command buffer.");

    // Begin recording a Vulkan command buffer.
    VkCommandBufferBeginInfo command_buffer_begin_info = {};
    command_buffer_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    command_buffer_begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    result = vkBeginCommandBuffer(command_buffer_, &command_buffer_begin_info);
    PLOG_FATAL_WHEN(result != VK_SUCCESS, "Renderer Vulkan", "Failed to begin recording Vulkan command buffer.");

    // End recording a Vulkan command buffer.
    vkEndCommandBuffer(command_buffer_);

    // Submit a Vulkan command buffer.
    VkQueue queue;
    vkGetDeviceQueue(device_, queue_family_index_, 0, &queue);

    VkSubmitInfo submit_info = {};
    submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = &command_buffer_;
    submit_info.signalSemaphoreCount = 0;
    submit_info.waitSemaphoreCount = 0;

    result = vkQueueSubmit(queue, 1, &submit_info, VK_NULL_HANDLE);
    PLOG_FATAL_WHEN(result != VK_SUCCESS, "Renderer Vulkan", "Failed to submit Vulkan command buffer.");

    vkQueueWaitIdle(queue);
}
}  //namespace pulsar