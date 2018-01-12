//
// Created by basti on 3/4/17.
//

#include <iostream>
#include "Ssh.h"



//ssh bbb@192.168.7.2 'sudo tcpdump -i wpan0 '

using namespace std;

string sshlocation = "/tmp/pipeRelay";
/*int example() {
    PipeWriter *wr = new PipeWriter(new string( sshlocation + "Out"), new string("PipeWriter"));
    wr->open();

    string *conf = new string("test");
    ReadConfig *r = new ReadConfig(conf);
    r->open();

    while (r->hasNext()){
        ReadConfig::entry * e = r->getNextValid();
        ssh * s = new ssh(e->client, e->user ,e->execute , wr);
        if(s->open()) {
          //  if (s->runConfig("26"))
            {
                cout << "\t setup success" << endl;
                char buff[20];
                s->read(buff, 20);
            }
          //  else {
           //    cerr << "error while setup remote client" << endl;
          //  }
        }
        else{
            cerr<< "error while opening ssh";
        }
    }
    cout <<endl;
}
*/
bool ssh::open() {
    if(setUp != "")
        remoteSetUp(setUp);
    string s = "ssh -q " + user +"@"+host + " '"+remoteExecute+"'" ; // -t
    Log::message(("ssh to " + host),("call: " + s) ,1);
    if(!(pipe = popen((s.c_str()), "r"))){
        cerr << "cout not open pipe:: "<< s<<endl;
        return false;
    }
    isOpen = true;
    return true;
}


void ssh::read(char *buffer, int size){
    if(!isOpen){
        Log::message("ssh reader","is not open",1);
        return;
    }

    fread(buffer,size,1,pipe);

}

bool ssh::remoteSetUp(string command){
    string s = "ssh -q " + user +"@"+host + " '"+command+"'" ; // -t
    Log::message(("ssh setup  to " + host),("call: " + s) ,1);
    FILE *device;
    if(!(device = popen((s.c_str()), "r"))){
        cerr << "cout not open device:: "<< s<<endl;
        return false;
    }
    //TODO setup + success challenge
    return true;
}