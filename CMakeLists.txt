cmake_minimum_required (VERSION 3.0)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
project (bam-tag-split)

find_package(Boost COMPONENTS system filesystem REQUIRED)

include_directories (include)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY dist)

add_executable (
    ${CMAKE_PROJECT_NAME}
    src/main.cpp
    src/options.cpp
)
target_link_libraries (
    ${CMAKE_PROJECT_NAME}
    hts
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)
