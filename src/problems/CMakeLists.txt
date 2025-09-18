# generate the executables for each problem in the problems folder
# so we can test with user inputs

file(GLOB_RECURSE PROBLEM_SOURCES CONFIGURE_DEPENDS *.cpp)

foreach(problem_src ${PROBLEM_SOURCES})
    # Get the filename without the directory or extension
    get_filename_component(problem_name ${problem_src} NAME_WE)

    set(projectName "Problem${problem_name}")

    # Create an executable with that name
    add_executable("${projectName}" ${problem_src})

    # Link the sut library
    target_link_libraries("${projectName}" PRIVATE sut)
endforeach()