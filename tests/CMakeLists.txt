# Core test.
set(core_test_target pfcore_test)
set(core_test_incdir "core")
set(core_test_deps Catch2::Catch2WithMain pfcore)
file(GLOB_RECURSE core_test_files
    "core/**.cpp"
    "core/**.hpp")

add_executable(${core_test_target} ${core_test_files})
target_link_directories(${core_test_target} PRIVATE ${core_test_incdir})
target_link_libraries(${core_test_target} PRIVATE ${core_test_deps})

add_test(NAME ${core_test_target} COMMAND $<TARGET_FILE:${core_test_target}>)
