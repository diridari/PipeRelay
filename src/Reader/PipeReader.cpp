//
// Created by Sebastian Balz  on 1/13/17.
//

#include "PipeReader.h"

#include <cstring>
#include <logging.h>

bool PipeReader::open(){

    char *tmp = createPipe();
    Log::log(name+ "please open in pipe e.g  [ \033[1;35m sudo tcpdump -U -s0 -w- > " + location   +" \033[0m]    or"
            "  [ \033[1;35m ssh <username>@<ip> 'sudo tcpdump -U -s0 -i wpan0 -w-' > " + location + " \033[0m]",UserInfo);
    inReader = new ifstream(tmp);
    Log::log(name+"Pipe : "+location +"is now open",Message);
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
       Log::log(name+"pipe is not open",CriticError);
        return;
    }


        inReader->read(buffer,size);
    if(!inReader)
        Log::log(name+"error with while reading the pipe ",CriticError);

}