//
// Created by basti on 1/29/17.
//
#include <logging.h>
#include "PipeHandler.h"



char* PipeHandler::createPipe(){
    char *tmp = new char(location.size());
    strcpy(tmp,location.c_str());

    if(!remove(tmp))
        Log::log(name+"delete old Pipe",Info);
    if(mkfifo(tmp,0666) != 0){
        cerr<< name <<"  init: Could not open the pipe located at: " <<location<<endl;
    }
    else{
        Log::log(name+"create Pipe",Info);
    }
    return tmp;
}
