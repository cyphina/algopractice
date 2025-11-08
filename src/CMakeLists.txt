file(GLOB_RECURSE ALGO_SOURCES CONFIGURE_DEPENDS
    binarysearch/*.cpp
    graph/*.cpp
    sorting/*.cpp
    divideAndConquer/*.cpp
    core/*.cpp
    misc/*.cpp
    tree/*.cpp
    memoization/*.cpp
)

file(GLOB_RECURSE ALGO_HEADERS CONFIGURE_DEPENDS
    binarysearch/*.h
    graph/*.h
    sorting/*.h
    divideAndConquer/*.h
    core/*.h
    misc/*.h
    tree/*.h
    memoization/*.h
)

# Combine all source files
set(ALL_ALGO_FILES ${ALGO_SOURCES} ${ALGO_HEADERS})

# Generate Visual Studio filters based on folder structure
foreach(_file IN LISTS ALL_ALGO_FILES)
    get_filename_component(_dir "${_file}" PATH)
    file(RELATIVE_PATH _group "${CMAKE_SOURCE_DIR}" "${_dir}")
    string(REPLACE "/" "\\" _group "${_group}")
    source_group("${_group}" FILES "${_file}")
endforeach()

add_library(sut STATIC ${ALGO_SOURCES})

target_sources(sut PRIVATE ${ALGO_HEADERS})

# compiler has rules on include lookup but we need to extend it to use our target paths
# also make it public so our test target can get this too.
target_include_directories(sut PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# use after we defined sut
add_subdirectory(problems)