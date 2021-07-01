# basic_executable_test
if(ENABLE_TESTS)
    # Add base/wolfvision/main.cpp to executable
    add_executable(wv-test "test_camera.cpp")

    # Add shared library link to target
    target_link_libraries(wv-test
        PUBLIC
        fmt::fmt-header-only
    )

    add_test(NAME test-wv-test COMMAND COMMAND wv-test)
endif()
