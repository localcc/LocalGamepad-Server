cmake_minimum_required(VERSION 3.15)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

project(LocalGamepad_Server)
set(CMAKE_CXX_STANDARD 20)

find_package()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(udp_server_src
        ${CMAKE_CURRENT_SOURCE_DIR}/include/udp_server/udp_server.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/udp_server/udp_client.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/udp_server/udp_server.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/udp_server/udp_client.cpp)

set(controller_src
        ${CMAKE_CURRENT_SOURCE_DIR}/include/controller/controller.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/controller/controller.cpp)

add_executable(${PROJECT_NAME} main.cpp ${udp_server_src} ${controller_src})

if(WIN32)
    target_link_libraries(${PROJECT_NAME} ws2_32 wsock32)
endif()