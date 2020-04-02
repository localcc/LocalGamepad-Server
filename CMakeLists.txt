cmake_minimum_required(VERSION 3.15)
include(ExternalProject)

project(LocalGamepad_Server)
set(CMAKE_CXX_STANDARD 20)
set(EXTERNAL_PROJECTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(udp_server_src
        ${CMAKE_CURRENT_SOURCE_DIR}/include/udp_server/udp_server.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/udp_server/udp_server.cpp)

set(controller_src
        ${CMAKE_CURRENT_SOURCE_DIR}/include/controller/controller.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/controller/controller_offsets.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/controller/controller_conversions.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/controller/controller.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/controller/controller_conversions.cpp
        )

add_executable(${PROJECT_NAME} main.cpp ${udp_server_src} ${controller_src})


if(WIN32)
    file(TO_NATIVE_PATH ${EXTERNAL_PROJECTS_DIR}/vigemclient/bin/$<IF:$<CONFIG:Debug>,debug,release>/x64/ViGEmClient.dll vigemclient_src_dll)
    file(TO_NATIVE_PATH ${CMAKE_CURRENT_BINARY_DIR}/ViGEmClient.dll vigemclient_dst_dll)
    ExternalProject_Add(vigemclient
            SOURCE_DIR ${EXTERNAL_PROJECTS_DIR}/vigemclient
            BUILD_IN_SOURCE TRUE
            GIT_REPOSITORY https://github.com/ViGEm/ViGEmClient.git
            GIT_PROGRESS TRUE
            BUILD_COMMAND msbuild ViGEmClient.sln /t:Build /p:Configuration=$<IF:$<CONFIG:Debug>,Debug_DLL,Release_DLL> /p:Platform=x64
            INSTALL_COMMAND copy ${vigemclient_src_dll} ${vigemclient_dst_dll}
            CONFIGURE_COMMAND ""
            )
    include_directories(${EXTERNAL_PROJECTS_DIR}/vigemclient/include)
    add_dependencies(${PROJECT_NAME} vigemclient)
    find_library(vigemclient_library NAMES ViGEmClient HINTS ${EXTERNAL_PROJECTS_DIR}/vigemclient/bin/$<IF:$<CONFIG:Debug>,debug,release>/x64)
    target_link_libraries(${PROJECT_NAME} ws2_32 wsock32 ${vigemclient_library})

endif()