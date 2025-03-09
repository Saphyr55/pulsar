# 
set(target_core pfcore)
set(incdir "./source")

file(GLOB_RECURSE sources
    "./source/**.hpp"
    "./source/**.cpp"
    "./source/**.inl")

add_library(${target_core})

target_sources(${target_core} PRIVATE ${sources})
target_include_directories(${target_core} PUBLIC ${incdir})

target_compile_definitions(${target_core} PRIVATE PULSAR_CORE_MODULE)
target_compile_definitions(${target_core} PRIVATE PULSAR_CORE_EXPORT)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sources})

