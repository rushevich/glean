cmake_minimum_required(VERSION 3.15)
project(glean LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(APPLE)
    execute_process(COMMAND brew --prefix mupdf-tools
        OUTPUT_VARIABLE MUPDF_PREFIX
        OUTPUT_STRIP_TRAILING_WHITESPACE)
    list(APPEND CMAKE_PREFIX_PATH "${MUPDF_PREFIX}")
endif()

find_path(MUPDF_INCLUDE_DIR mupdf/fitz)
find_library(MUPDF_LIB mupdf)
find_library(MUPDF_THIRD_LIB mupdf-third)

if(NOT MUPDF_INCLUDE_DIR OR NOT MUPDF_LIB OR NOT MUPDF_THIRD_LIB)
    message(FATAL_ERROR "MuPDF not found. Install with: brew install mupdf-tools")
endif()

add_executable(glean src/main.cpp src/wrapper/context.cpp src/wrapper/pixmap.cpp src/wrapper/document.cpp src/wrapper/pdf.cpp)

target_include_directories(glean PRIVATE
    ${MUPDF_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(glean PRIVATE
    ${MUPDF_LIB}
    ${MUPDF_THIRD_LIB})

target_compile_options(glean PRIVATE -Wall -Wextra -Werror -g #[[-fsanitize=address]])
# target_link_options(glean PRIVATE -fsanitize=address)
