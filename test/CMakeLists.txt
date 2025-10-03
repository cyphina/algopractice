include(FetchContent)
FetchContent_Declare(Catch2 GIT_REPOSITORY https://github.com/catchorg/Catch2.git GIT_TAG v3.4.0)
FetchContent_MakeAvailable(Catch2)

file(GLOB_RECURSE ALGO_SOURCES CONFIGURE_DEPENDS
    cppFeatures/*.cpp
    divideAndConquer/*.cpp
    graph/*.cpp
    sorting/*.cpp
    core/*.cpp
    misc/*.cpp
    memoization/*.cpp
)

# Generate Visual Studio filters based on folder structure
foreach(_file IN LISTS ALGO_SOURCES)
    get_filename_component(_dir "${_file}" PATH)
    file(RELATIVE_PATH _group "${CMAKE_SOURCE_DIR}" "${_dir}")
    string(REPLACE "/" "\\" _group "${_group}")
    source_group("${_group}" FILES "${_file}")
endforeach()

add_executable(unit_tests ${ALGO_SOURCES})

target_link_libraries(unit_tests PRIVATE sut Catch2::Catch2WithMain)

# When we call `include` we need to make sure this path is in the list of directories to search.
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
# Reference other script files or modules.
include(Catch)
# Runs test binary once at configure time with --list-tests. Parses list of test cases. Registers each with `add_test()` in CMake.
catch_discover_tests(unit_tests)