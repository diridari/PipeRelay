cmake_minimum_required(VERSION 3.6)
project(PipeRelay)



set(CMAKE_CXX_STANDARD 11)

include_directories(include)

set(SOURCE_FILES src/Writer/PipeWriter.cpp include/PipeWriter.h src/Reader/PipeReader.cpp
        include/PipeReader.h include/Log.h src/Loging/Log.cpp include/PipeHandler.h src/Pipehandler.cpp
        include/ReadConfig.h src/ssh/Ssh.cpp include/Ssh.h src/ssh/ReadConfig.cpp
        src/BaseReader.cpp include/BaseReader.h)
set(SOURCE_FILES_Exec  ${SOURCE_FILES} main.cpp  )


## Cmake for building a Executable
add_executable(PipeRelay ${SOURCE_FILES_Exec} )
target_link_libraries(PipeRelay  pthread)

## Cmake to build a library
ADD_LIBRARY( PipeRelayLib STATIC ${SOURCE_FILES})
target_link_libraries(PipeRelayLib  pthread)