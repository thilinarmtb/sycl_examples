cmake_minimum_required(VERSION 3.24)
project(sycl_examples VERSION 0.0.1 DESCRIPTION "" LANGUAGES CXX)

option(ENABLE_DOCS "Enable Documentation" OFF)
option(ENABLE_ASAN "Enable AddressSanitizer" OFF)

# https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/RPATH-handling
# Use, i.e. don't skip the full RPATH for the build tree.
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
# When building, don't use the install RPATH.
set(CMAKE_SKIP_BUILD_RPATH FALSE)
# Set the library location.
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
# Add the automatically determined parts of the RPATH which point to directories
# outside the build tree to the install RPATH.
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Turn on AddressSanitizer if ENABLE_ASAN is set.
if (ENABLE_ASAN)
  include(CheckLinkerFlag)
  check_linker_flag(CXX -fsanitize=address HAS_ADDRESS_SANITIZER)
  if (NOT HAS_ADDRESS_SANITIZER)
    message(FATAL_ERROR "AddressSanitizer is enabled but not supported.")
  endif()
endif()

macro(add_examples examples)
  foreach (example ${examples})
    string(REPLACE "${CMAKE_SOURCE_DIR}/src/" "" example_cpp ${example})
    string(REPLACE ".cpp" "" example_exe ${example_cpp})
    add_executable(${example_exe} ${example})
    target_include_directories(${example_exe} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_compile_options(${example_exe} PRIVATE
      $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>)
    if (HAS_ADDRESS_SANITIZER)
      target_compile_options(${example_exe} PRIVATE -fsanitize=address)
      target_link_options(${example_exe} PRIVATE -fsanitize=address)
    endif()
    install(TARGETS ${example_exe} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
  endforeach()
endmacro()

file(GLOB SOURCES src/*.cpp)
add_examples("${SOURCES}")

# Add clang-format as a custom target if available.
find_program(CLANG_FORMAT NAMES clang-format)
if (CLANG_FORMAT)
  add_custom_target(format
    COMMAND ${CLANG_FORMAT} -i ${CMAKE_CURRENT_SOURCE_DIR}/*/*.[ch]
    COMMENT "Running clang-format ...")
  add_custom_target(format-check
    COMMAND ${CLANG_FORMAT} --dry-run -Werror -i ${CMAKE_CURRENT_SOURCE_DIR}/*/*.[ch]
    COMMENT "Running clang-format check ...")
endif()

# Configure .clang-tidy.in to generate .clang-tidy.
configure_file(${CMAKE_SOURCE_DIR}/.clang-tidy.in ${CMAKE_SOURCE_DIR}/.clang-tidy @ONLY)
# Add clang-tidy as a custom target if available.
find_program(CLANG_TIDY NAMES clang-tidy)
if (CLANG_TIDY)
  add_custom_target(tidy
    COMMAND ${CLANG_TIDY} -p ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*/*.[ch]
    COMMENT "Running clang-tidy ...")
endif()

if (ENABLE_DOCS)
  add_subdirectory (docs)
endif()
