# 
set(target_runtime pfruntime)
set(incdir "./source")
set(deps_runtime pfcore)

file(GLOB_RECURSE sources_runtime
    "./source/**.hpp"
    "./source/**.cpp"
    "./source/**.inl")

add_library(${target_runtime})

target_sources(${target_runtime} PRIVATE ${sources_runtime})
target_include_directories(${target_runtime} PUBLIC ${incdir})
target_link_libraries(${target_runtime} PUBLIC ${deps_runtime})

target_compile_definitions(${target_runtime} PRIVATE PULSAR_RUNTIME_MODULE)
target_compile_definitions(${target_runtime} PRIVATE PULSAR_RUNTIME_EXPORT)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sources_runtime})
