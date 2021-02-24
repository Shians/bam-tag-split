cmake_minimum_required (VERSION 3.0)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
project (bam-tag-tools)

find_package (Boost COMPONENTS system filesystem REQUIRED)

add_subdirectory (include/fmt)

include_directories (include include/fmt/include)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY dist)

set (SPLIT_PROG bam-tag-split)
add_executable (
    ${SPLIT_PROG}
    src/split.cpp
    src/split_options.cpp
)

target_link_libraries (
    ${SPLIT_PROG}
    hts
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

install(TARGETS ${SPLIT_PROG} DESTINATION bin)

set (EXTRACT_PROG bam-tag-extract)
add_executable (
    ${EXTRACT_PROG}
    src/extract.cpp
    src/extract_options.cpp
)

target_link_libraries (
    ${EXTRACT_PROG}
    hts
    fmt::fmt
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

install(TARGETS ${EXTRACT_PROG} DESTINATION bin)

