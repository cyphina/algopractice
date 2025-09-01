file(GLOB_RECURSE ALGO_SOURCES CONFIGURE_DEPENDS
    graph/*.cpp
    sorting/*.cpp
    divideAndConquer/*.cpp
)
add_library(sut STATIC ${ALGO_SOURCES})

file(GLOB_RECURSE ALGO_HEADERS CONFIGURE_DEPENDS
    graph/*.h
    sorting/*.h
    divideAndConquer/*.h
)

target_sources(sut PRIVATE ${ALGO_HEADERS})

target_include_directories(sut PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(main main.cpp)
target_link_libraries(main PRIVATE sut)