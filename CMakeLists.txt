cmake_minimum_required(VERSION 3.5)
project(PipeRelay)



set(CMAKE_CXX_STANDARD 11)

include_directories(include)

set(PipeMerge_Files src/Writer/PipeWriter.cpp include/PipeWriter.h src/Reader/PipeReader.cpp
        include/PipeReader.h include/PipeHandler.h src/Pipehandler.cpp
        include/ReadConfig.h src/ssh/Ssh.cpp include/Ssh.h src/ssh/ReadConfig.cpp
        src/BaseReader.cpp include/BaseReader.h)
set(SOURCE_FILES_Exec  ${PipeMerge_Files} main.cpp  main.h)


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
add_executable(PipeRelay ${SOURCE_FILES_Exec} )
ADD_DEPENDENCIES(PipeRelay simpleLogging)
target_link_libraries(PipeRelay  pthread SimpleLoggingLib)


## Cmake to build a library
ADD_LIBRARY( PipeRelayLib STATIC ${PipeMerge_Files})
ADD_DEPENDENCIES(PipeRelayLib simpleLogging)
target_link_libraries(PipeRelayLib  pthread SimpleLoggingLib)

