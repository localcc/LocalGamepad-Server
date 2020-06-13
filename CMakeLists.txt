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
        ${CMAKE_CURRENT_SOURCE_DIR}/include/controller/controller_conversion.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/controller/controller_offsets.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/controller/controller.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/controller/controller_conversion.cpp
        )

add_executable(${PROJECT_NAME} main.cpp ${udp_server_src} ${controller_src})


if(WIN32)
# I fell like I'm doing something wrong
	file(TO_NATIVE_PATH ${EXTERNAL_PROJECTS_DIR}/ViGEm/bin/$<IF:$<CONFIG:Debug>,debug,release>/x64/ViGEmClient.dll vigemclient_src_dll)
    file(TO_NATIVE_PATH ${CMAKE_CURRENT_BINARY_DIR}/ViGEmClient.dll vigemclient_dst_dll)

	ExternalProject_Add(
		vigem_library
		SOURCE_DIR ${EXTERNAL_PROJECTS_DIR}/ViGEm
		BUILD_IN_SOURCE TRUE
		GIT_REPOSITORY https://github.com/ViGEm/ViGEmClient.git
		GIT_PROGRESS TRUE
		BUILD_COMMAND msbuild ViGEmClient.sln /t:Build /p:Configuration=$<IF:$<CONFIG:Debug>,Debug_DLL,Release_DLL> /p:Platform=x64
		INSTALL_COMMAND copy ${vigemclient_src_dll} ${vigemclient_dst_dll}
		CONFIGURE_COMMAND ""
	)
	add_dependencies(${PROJECT_NAME} vigem_library)
	ExternalProject_Get_Property(vigem_library source_dir)
	include_directories(${source_dir}/include)
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		message("Debug")
		target_link_libraries(${PROJECT_NAME} ${source_dir}/bin/debug/x64/ViGEmClient.lib ws2_32 wsock32)
	else()
		message("Release")
		target_link_libraries(${PROJECT_NAME} ${source_dir}/bin/release/x64/ViGEmClient.lib ws2_32 wsock32)
	endif()
endif()