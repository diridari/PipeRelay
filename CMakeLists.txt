cmake_minimum_required(VERSION 3.6)
project(PipeRelay)



set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES  main.cpp PipeRelay/Writer/PipeWriter.cpp PipeRelay/Writer/PipeWriter.h PipeRelay/Reader/PipeReader.cpp
        PipeRelay/Reader/PipeReader.h Loging/Log.h Loging/Log.cpp PipeRelay/PipeHandler.h PipeRelay/Pipehandler.cpp
        PipeRelay/ssh/ReadConfig.h PipeRelay/ssh/Ssh.cpp PipeRelay/ssh/Ssh.h PipeRelay/ssh/ReadConfig.cpp
        PipeRelay/BaseReader.cpp PipeRelay/BaseReader.h )


add_executable(PipeRelay ${SOURCE_FILES} )

target_link_libraries(PipeRelay  pthread)