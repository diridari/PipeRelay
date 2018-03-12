cmake_minimum_required(VERSION 3.5)
project(PipeMerge)



set(CMAKE_CXX_STANDARD 11)

include_directories(include)

set(PipeMerge_Files src/Writer/PipeWriter.cpp include/PipeWriter.h src/Reader/PipeReader.cpp
        include/PipeReader.h include/PipeHandler.h src/Pipehandler.cpp
        include/ReadConfig.h src/ssh/Ssh.cpp include/Ssh.h src/ssh/ReadConfig.cpp
        src/BaseReader.cpp include/BaseReader.h)

set (TestFiles  Test/init.cpp Test/init.cpp Test/gtest/gtest.h Test/gtest/gtest-all.cc Test/sshConfig/sshConfigTest.cpp
        )

include(ExternalProject)
externalProject_add(
        simpleLogging
        GIT_REPOSITORY https://github.com/diridari/SimpleLogging.git
        CONFIGURE_COMMAND   cmake CMakeLists.txt
        BUILD_IN_SOURCE ON
        INSTALL_COMMAND make SimpleLoggingLib   # make target
)

ExternalProject_Get_Property(simpleLogging SOURCE_DIR)
ExternalProject_Get_Property(simpleLogging BINARY_DIR)
include_directories(${SOURCE_DIR}/include) # include simpleLog/inlude
LINK_DIRECTORIES(${BINARY_DIR}) ## link git build lib



## Cmake for building a Executable
add_executable(PipeMerge ${PipeMerge_Files} ${SOURCE_DIR} main.cpp  main.h)
add_executable(PipeMergeTest ${PipeMerge_Files} ${SOURCE_DIR} ${TestFiles} )



## Cmake to build a library
ADD_LIBRARY( PipeMergeLib STATIC ${PipeMerge_Files} ${SOURCE_DIR})

ADD_DEPENDENCIES(PipeMerge simpleLogging)
ADD_DEPENDENCIES(PipeMergeTest simpleLogging)
ADD_DEPENDENCIES(PipeMergeLib simpleLogging)


target_link_libraries(PipeMerge  pthread SimpleLoggingLib)
target_link_libraries(PipeMergeLib  pthread SimpleLoggingLib)
target_link_libraries(PipeMergeTest pthread SimpleLoggingLib)