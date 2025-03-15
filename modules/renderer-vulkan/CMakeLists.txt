# 
set(target_runtime pfrenderer_vulkan)
set(incdir "./source")
set(deps_runtime pfcore pfruntime)

file(GLOB_RECURSE sources_runtime
    "./source/**.hpp"
    "./source/**.cpp"
    "./source/**.inl")

add_library(${target_runtime} SHARED)

list(APPEND ${deps_runtime} Vulkan::Vulkan)

target_sources(${target_runtime} PRIVATE ${sources_runtime})
target_include_directories(${target_runtime} PUBLIC ${incdir} PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(${target_runtime} PUBLIC ${deps_runtime} PRIVATE ${Vulkan_LIBRARIES})

target_compile_definitions(${target_runtime} PRIVATE PULSAR_RENDERER_VULKAN_MODULE)
target_compile_definitions(${target_runtime} PRIVATE PULSAR_RENDERER_VULKAN_EXPORTS)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sources_runtime})
