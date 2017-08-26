//
// Created by basti on 3/3/17.
//

#include "ReadConfig.h"
#include <fstream>


void exampleConfig () {
    ReadConfig *r = new ReadConfig(new string("test"));
    r->open();

    while (r->hasNext()){
        ReadConfig::entry * e = r->getNextValid();
        cout << "client: "<<e->client<< " \t user:" <<e->user <<"\t exc: "<< e->execute<< "\t"<<endl;
    }

cout <<"ende"<<endl;

}

void ReadConfig::open() {
    reader = new ifstream(name->c_str(), std::ifstream::in);
    if(!reader->is_open()){
        Log::message("Config parser","could not open config File",0);
        exit(-1);
    }
    entry * e = enceodeLine(readLine());
    Log::message("Config parser","open config parser",3);

    while(hasNextTmp && !e->valid){
        e = enceodeLine(readLine());
    }
    if(hasNextTmp) {
        next = e;

        hasnext = true;
    }
    else
        hasnext = false;
}

string * ReadConfig::readLine() {

    string * out = new string("");
    char c = reader->get();
    while(c != -1 && c != '\n' ){
        if(c != '\t' && c!= '\r')
            *out += c;
        c = reader->get();
    }

    return out;
}

ReadConfig::entry* ReadConfig::enceodeLine(string *line) {
    Log::message("Config parser","encode line " + *line,3);
    string *client = new string("");
    string *user = new string("");
    string *exc = new string("");
    bool isClient = true;
    bool isUser = false;
    lineIndex ++;
    char c;
    for(int index = 0; index < line->size(); index++){
       if(isClient) {
           if (line->at(index) != ' ')
               *client += line->at(index);
           else {
               isUser = true;
               isClient = false;
           }
       }
       else if(isUser){
           if(line->at(index) != ' ')
                *user += line->at(index);
           else
                isUser = false;
           }
        else
            *exc += line->at(index);


    }

     hasNextTmp = !(*user == "" && *client == "" && *exc == "");
    bool valid = (*user != "" && *client != "" && *exc != "");
    ReadConfig::entry *newEntry = new entry(*client, *user, *exc,valid );
    Log::message("Config parser ",("encode line " + *user  + "  " + *client + " " + *exc),2);

    if(!valid && hasNextTmp)
        cerr << "unvalid entry in line "<<lineIndex<<" : "<<*line<<endl;
    return newEntry;
}

ReadConfig::entry* ReadConfig::getNextValid() {

    if(!hasNext())
        return NULL;
    entry *tmp = next;
    entry * e = enceodeLine(readLine());
    while(hasNextTmp && !e->valid) {
       Log::message("Config Parser"," read next",3);
        string *line = readLine();
        e = enceodeLine(line);
    }
    next = e;

    if(!hasNextTmp) {
        hasnext = false;

    }
    return tmp;
}

bool ReadConfig::isValid(entry *that){
    bool is =  (that->user != "" && that->client != "" && that->execute != "") ;
    that->valid = is;
    return is;
}
