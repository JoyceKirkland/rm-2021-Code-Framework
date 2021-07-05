# Create project
cmake_minimum_required(VERSION 3.10.0)
project(WolfVision VERSION 1.0.0 LANGUAGES CXX)

# Specialize CMake build flags for different build types
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Use standard c++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Prefer posix threads
# set(THREADS_PREFER_PTHREAD_FLAG True)
# find_package(Threads REQUIRED)

# Find and add opencv as required
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Add fmtlib directory and include path for target
add_subdirectory(3rdparty/fmt EXCLUDE_FROM_ALL)

# Add fmtlib include to EXTRA_INCLUDES
list(APPEND EXTRA_INCLUDES 3rdparty/fmt/include)

# Add mindvision linux sdk
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Add mindvision-sdk directory and include path for target
    add_library(MVSDK SHARED IMPORTED)
    get_filename_component(MVSDK_PATH 3rdparty/mindvision/linux REALPATH)

    # Check system architecture for mindvision-sdk library
    EXECUTE_PROCESS(COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE)
    message(STATUS "Checking platform architecture for MVSDK: ${ARCHITECTURE}")
    if(${ARCHITECTURE} STREQUAL x86_64)
        set(MIMDVISION_SDK_LIBRARY ${MVSDK_PATH}/lib/x64/libMVSDK.so)
    elseif(${ARCHITECTURE} STREQUAL x86)
        set(MIMDVISION_SDK_LIBRARY ${MVSDK_PATH}/lib/x86/libMVSDK.so)
    elseif(${ARCHITECTURE} STREQUAL aarch64)
        set(MIMDVISION_SDK_LIBRARY ${MVSDK_PATH}/lib/arm64/libMVSDK.so)
    elseif(${ARCHITECTURE} STREQUAL armv7)
        set(MIMDVISION_SDK_LIBRARY ${MVSDK_PATH}/lib/arm/libMVSDK.so)
    else()
        message(FATAL_ERROR "Not supported architecture for MVSDK: ${ARCHITECTURE}")
    endif()
    set_property(TARGET MVSDK PROPERTY IMPORTED_LOCATION ${MIMDVISION_SDK_LIBRARY})

    # Add mindvision include path
    list(APPEND EXTRA_INCLUDES 3rdparty/mindvision/linux/include)
endif()

# Add user/main.cpp to executable
add_executable(WolfVision user/main.cpp)

# Add base src and header
list(APPEND EXTRA_INCLUDES base)

# Add device as shared library to build target
list(APPEND EXTRA_INCLUDES devices)

list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/devices/camera)
add_library(wv-devices-camera SHARED devices/camera/rm_video_capture.cpp)
list(APPEND EXTRA_LIBS wv-devices-camera)

list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/devices/serial)
add_library(wv-devices-serial SHARED devices/serial/rm_serial_port.cpp)
list(APPEND EXTRA_LIBS wv-devices-serial)

# Add module as shared library to build target
list(APPEND EXTRA_INCLUDES module)

list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/module/angle_solve)
add_library(wv-module-angle-solve SHARED module/angle_solve/rm_solve_pnp.cpp)
list(APPEND EXTRA_LIBS wv-module-angle-solve)

list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/module/armor)
add_library(wv-module-armor SHARED module/armor/rm_armor_detection.cpp)
list(APPEND EXTRA_LIBS wv-module-armor)

list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/module/buff)
add_library(wv-module-buff SHARED module/buff/rm_buff_detection.cpp)
list(APPEND EXTRA_LIBS wv-module-buff)

list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/module/filter)
add_library(wv-module-filter SHARED module/filter/rm_kalman_filter.cpp)
list(APPEND EXTRA_LIBS wv-module-filter)

list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/module/object_detection)
add_library(wv-module-object-detection SHARED module/object_detection/rm_dnn_yolov4.cpp)
list(APPEND EXTRA_LIBS wv-module-object-detection)

list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/module/roi)
add_library(wv-module-roi SHARED module/roi/rm_roi.cpp)
list(APPEND EXTRA_LIBS wv-module-roi)

# Add EXTRA_INCLUDES to project includes
include_directories(${EXTRA_INCLUDES})

# Add shared library link to target
target_link_libraries(WolfVision
    PUBLIC
    # Threads::Threads
    fmt::fmt-header-only
    ${OpenCV_LIBS}

    PRIVATE
    ${EXTRA_LIBS}
)

# Set WolfVision compile features to standared c++14
target_compile_features(WolfVision PUBLIC cxx_std_14)

# Set built binary to ~/bin
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

# Set built library to ~/lib
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")
