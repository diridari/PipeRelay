//
// Created by Sebastian Balz  on 1/13/17.
//

#include "PipeReader.h"

#include <cstring>
bool PipeReader::open(){

    char *tmp = createPipe();
    Log::message(name, "please open in pipe e.g  [ \033[1;35m sudo tcpdump -U -s0 -w- > " + location   +" \033[0m]    or"
            "  [ \033[1;35m ssh <username>@<ip> 'sudo tcpdump -U -s0 -i wpan0 -w-' > " + location + " \033[0m]",0);
    inReader = new ifstream(tmp);
    Log::message(name,"Pipe : "+location +"is now open",1);
    isOpen = true;
    return inReader->is_open();
}


void PipeReader::close(){
    isOpen = false;
    inReader->close();
    delete inReader;

}


void PipeReader::read(char * buffer, int size){
    if(!isOpen) {
       Log::message(name,"pipe is not open",0);
        return;
    }


        inReader->read(buffer,size);
    if(!inReader)
        Log::message(name,"error with while reading the pipe ",0);

}