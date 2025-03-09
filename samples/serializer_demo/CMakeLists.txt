# 
set(target demo_serializer)
set(deps pfcore pfruntime)
set(incdir "./source")

file(GLOB_RECURSE sources
    "./source/**.hpp"
    "./source/**.cpp"
    "./source/**.inl")

add_executable(${target})

target_sources(${target} PRIVATE ${sources})
target_link_directories(${target} PRIVATE ${incdir})
target_link_libraries(${target} PRIVATE ${deps})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sources})
