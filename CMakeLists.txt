cmake_minimum_required (VERSION 2.6)
project (cpp_template)

IF (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
ENDIF()

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

set(cpp_template_VERSION_MAJOR 1)
set(cpp_template_VERSION_MINOR 0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall")

set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(DOXYGEN_DIRECTORY ${CMAKE_BINARY_DIR}/docs)

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/googletest)
    add_definitions(-DGTEST_USE)
    set(GTEST_USE TRUE)
else()
    set(GTEST_USE FALSE)
endif()

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/gnuplot-iostream)
    add_definitions(-DGNUPLOT_USE)
    set(GNUPLOT_USE TRUE)
else()
    set(GNUPLOT_USE FALSE)
endif()

set(DOXYGEN_USE TRUE)

if (GNUPLOT_USE)
    include_directories(gnuplot-iostream)

    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -lboost_iostreams -lboost_system -lboost_filesystem")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lboost_iostreams -lboost_system -lboost_filesystem")
endif()

add_subdirectory(src)

if (GTEST_USE)
    include_directories(googletest/googletest/include)
    add_subdirectory(googletest)
    enable_testing()

    include_directories(src)

    file( GLOB TEST_SOURCES tests/*_test.cpp )
    foreach( testfile ${TEST_SOURCES} )

        get_filename_component(testfile_dir ${testfile} DIRECTORY)
        get_filename_component(testfile_lastdir ${testfile_dir} NAME)
        get_filename_component(testfile_name_cpp ${testfile} NAME )
        string(REPLACE "_test.cpp" "" originalname ${testfile_name_cpp})
        string(REPLACE ".cpp" "" testname ${testfile_name_cpp})

        add_executable( ${testname} ${testfile})
        target_link_libraries(${testname} ${originalname} gtest gtest_main gmock)

    endforeach( testfile ${TEST_SOURCES})

endif()

if (DOXYGEN_USE)
    # Taken from https://vicrucann.github.io/tutorials/quick-cmake-doxygen/

    # first we can indicate the documentation build as an option and set it to ON by default
    option(BUILD_DOC "Build documentation" ON)

    # check if Doxygen is installed
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        # set input and output files
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
        #set(DOXYGEN_OUT ${DOXYGEN_DIRECTORY}/Doxyfile)

        # request to configure the file
        #configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message("Doxygen build started")

        # note the option ALL which allows to build the docs together with the application
        add_custom_target( doc_doxygen ALL
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_IN}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                COMMENT "Generating API documentation with Doxygen"
                VERBATIM )
    else (DOXYGEN_FOUND)
        message("Doxygen need to be installed to generate the doxygen documentation")
    endif (DOXYGEN_FOUND)
endif()