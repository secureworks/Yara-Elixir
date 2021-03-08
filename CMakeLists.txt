cmake_minimum_required(VERSION 3.19)
project(Yara-Elixir LANGUAGES C VERSION 0.1)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")

set(YE_NIF_TARGET Yara-Elixir)
set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE RelWithDebInfo)
#cmake -DCMAKE_BUILD_TYPE=Debug <path and other arguments>
#cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo <path and other arguments>
set(COMPILE_DEBUG_FLAGS -O0 -ggdb3)

set(CMAKE_C_FLAGS_DEBUG "-DDEBUG -O0 -ggdb3")
# set(CMAKE_C_FLAGS_MINSIZEREL "")
# set(CMAKE_C_FLAGS_RELWITHDEBINFO "")
# set(CMAKE_C_FLAGS_RELEASE "")

add_library(YE_NIF_TARGET
  SHARED
  shared/yara_elixir.c
  shared/yara_elixir.h
  shared/debug.c
)

include(FindErlang)

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${ERLANG_EI_LIBRARY_PATH})

find_library(ERLANG_EI_LIB ei)
find_library(ERLANG_ERL_INTERFACE_LIB erl_interface)
include_directories(${ERLANG_EI_INCLUDE_PATH})
include_directories(${ERLANG_ERTS_INCLUDE_PATH})

find_package(PkgConfig REQUIRED)
pkg_check_modules(YARA REQUIRED IMPORTED_TARGET yara)
message(STATUS "Using YARA version: ${YARA_VERSION}")
message(STATUS "Using YARA CFLAGS: ${YARA_CFLAGS}")
message(STATUS "Using YARA LDFLAGS: ${YARA_LDFLAGS}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -Wall")
set(TARGET_LINKER_OPTIONS)
if(APPLE)
  set(TARGET_LINKER_OPTIONS "-flat_namespace -undefined suppress")
endif()

target_include_directories(YE_NIF_TARGET
  PRIVATE
  ${DEFAULT_INCLUDE_DIRECTORIES}
)

target_link_libraries(YE_NIF_TARGET
  PRIVATE
  ${TARGET_LINKER_OPTIONS}
  PkgConfig::YARA
)

set_target_properties(YE_NIF_TARGET PROPERTIES PREFIX "lib")
set_target_properties(YE_NIF_TARGET PROPERTIES OUTPUT_NAME "yara_elixir")
set_target_properties(YE_NIF_TARGET PROPERTIES SUFFIX ".so")
