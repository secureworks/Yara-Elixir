cmake_minimum_required(VERSION 3.19)
project(Yara-Elixir LANGUAGES C VERSION 0.1)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake")
include(FindErlang)

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${ERLANG_EI_LIBRARY_PATH})

find_library(ERLANG_EI_LIB ei)
find_library(ERLANG_ERL_INTERFACE_LIB erl_interface)
include_directories(${ERLANG_EI_INCLUDE_PATH})
include_directories(${ERLANG_ERTS_INCLUDE_PATH})

set(TARGET_LINKER_OPTIONS)
if(APPLE)
	set(TARGET_LINKER_OPTIONS "-flat_namespace -undefined suppress")
endif(APPLE)

#execute_process(COMMAND
#    erl -noshell -eval "io:format(\"~ts/erts-~ts/include/\", [code:root_dir(), erlang:system_info(version)])." -s erlang halt
#    OUTPUT_VARIABLE ERLANG_OTP_ROOT_DIR)
#execute_process(COMMAND
#    erl -noshell -s init stop -eval "io:format(\"~ts\", [code:lib_dir(erl_interface, lib)])."
#    OUTPUT_VARIABLE ERLANG_INTERFACE_LIB_DIR)

message(STATUS "erl eval: ${ERLANG_OTP_ROOT_DIR}")
message(STATUS "erl eval 2: ${ERLANG_INTERFACE_LIB_DIR}")

add_library(yara_elixir SHARED
            shared/yara_elixir.c)
target_include_directories(yara_elixir PRIVATE ${ERLANG_OTP_ROOT_DIR})
find_package(PkgConfig REQUIRED)
pkg_check_modules (YARA REQUIRED IMPORTED_TARGET yara)
target_link_libraries(yara_elixir PUBLIC PkgConfig::YARA)
