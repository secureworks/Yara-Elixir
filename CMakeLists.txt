cmake_minimum_required(VERSION 3.19)
project(Yara-Elixir LANGUAGES C VERSION 0.1)

set(YE_NIF_TARGET Yara-Elixir)
set(CMAKE_C_STANDARD 11)

add_library(YE_NIF_TARGET SHARED shared/yara_elixir.c)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake")
include(FindErlang)

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${ERLANG_EI_LIBRARY_PATH})

find_library(ERLANG_EI_LIB ei)
find_library(ERLANG_ERL_INTERFACE_LIB erl_interface)
include_directories(${ERLANG_EI_INCLUDE_PATH})
include_directories(${ERLANG_ERTS_INCLUDE_PATH})

find_package(PkgConfig REQUIRED)
pkg_check_modules (YARA REQUIRED IMPORTED_TARGET yara)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
set(TARGET_LINKER_OPTIONS)
if(APPLE)
	set(TARGET_LINKER_OPTIONS "-flat_namespace -undefined suppress")
endif(APPLE)

#target_sources(YE_NIF_TARGET
#    PRIVATE
#    ${CMAKE_CURRENT_SOURCE_DIR}/shared/yara_elixir.c}
#)

target_include_directories(YE_NIF_TARGET
    PRIVATE
    ${DEFAULT_INCLUDE_DIRECTORIES}
)

target_link_libraries(YE_NIF_TARGET
    PRIVATE
    ${TARGET_LINKER_OPTIONS}
    PkgConfig::YARA
)
