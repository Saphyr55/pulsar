# 
set(target demo01)
set(deps pfcore pfruntime pfplatform pfrenderer_vulkan)
set(incdir "./source")

file(GLOB_RECURSE sources
    "./source/**.hpp"
    "./source/**.cpp"
    "./source/**.inl")

if(WIN32)
    add_executable(${target} WIN32)
else()
    add_executable(${target})
endif(WIN32)


target_sources(${target} PRIVATE ${sources})
target_link_directories(${target} PRIVATE ${incdir})
target_link_libraries(${target} PRIVATE ${deps})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sources})
