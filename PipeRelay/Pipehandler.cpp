//
// Created by basti on 1/29/17.
//
#include "PipeHandler.h"



char* PipeHandler::createPipe(){
    char *tmp = new char(location.size());
    strcpy(tmp,location.c_str());

    if(!remove(tmp))
        Log::message(name,"delete old Pipe",3);
    if(mkfifo(tmp,0666) != 0){
        cerr<< name <<"  init: Could not open the pipe located at: " <<location<<endl;
    }
    else{
        Log::message(name,"create Pipe",3);
    }
    return tmp;
}
