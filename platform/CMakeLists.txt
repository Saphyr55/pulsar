# 
set(target_platform pfplatform)
set(incdir "./source")
set(deps_platform pfruntime pfcore)

file(GLOB_RECURSE sources_platform
    "./source/**.hpp"
    "./source/**.cpp"
    "./source/**.inl")

add_library(${target_platform} STATIC)

target_sources(${target_platform} PRIVATE ${sources_platform})
target_include_directories(${target_platform} PUBLIC ${incdir})
target_link_libraries(${target_platform} PUBLIC ${deps_platform})

target_compile_definitions(${target_platform} PRIVATE PULSAR_PLATFORM_MODULE)
target_compile_definitions(${target_platform} PRIVATE PULSAR_PLATFORM_EXPORT)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sources_platform})
