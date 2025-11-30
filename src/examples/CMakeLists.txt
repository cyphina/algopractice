# generate the executables for each problem in the problems folder
# so we can test with user inputs

file(GLOB_RECURSE EXAMPLE_SOURCES CONFIGURE_DEPENDS *.cpp)

foreach(example_src ${EXAMPLE_SOURCES})
    # Get the filename without the directory or extension
    get_filename_component(example_name ${example_src} NAME_WE)

    set(projectName "Example${example_name}")

    # Create an executable with that name
    add_executable("${projectName}" ${example_src})

    # Link the sut library
    target_link_libraries("${projectName}" PRIVATE sut)
endforeach()