//
// Created by Sebastian Balz  on 1/13/17.
//

#include "PipeWriter.h"


bool PipeWriter::open(){
    char *tmp = createPipe();
    isOpen = true;
    Log::message(name, "please open in pipe e.g [\033[1;36m cat " + location + " | sudo wireshark -k -i- \033[0m ]",0); //
    fwriter = new ofstream(tmp);
    Log::message(name,"out pipe is now open",1);
    delete tmp;
    return fwriter->is_open();
}


void PipeWriter::write(char *buffer, int size) {
    if(!isOpen){
        cerr << name << "write()  is not open"<<endl;
        return;
    }
    locker.lock();
    fwriter->write(buffer,size);
    fwriter->flush();

    if(writeLog){
        Log::message(name,"write bytes from char array",2);
        loger->write(buffer,size);
        loger->flush();
    }
    locker.unlock();

}

void PipeWriter::close(){
    isOpen = false;
    fwriter->close();
    loger->close();
    delete loger;
    delete fwriter;
    remove(loglocation);

}
