//
// Created by basto on 6/26/17.
//

#include "BaseReader.h"
/*
 void BaseReader::readUntilSignatur(char *buffer, int size) {
     bool found = false;
     char tmp;
     while(!found){
         read(&tmp,1);
         while(tmp != buffer[0]){
             read(&tmp,1);
         }
         for(int i = 1; i< size; i++){
             read(&tmp,1);
             if(tmp != buffer[i])
                 break;
             else if(i == size)
                 found = true;
         }
     }

 }
 */
void BaseReader::readUntilSignatur(char *buffer, int size) {
    bool isFinish = false;
    int pos = 0;

    while (!isFinish) {
        char c;
       read(&c,1);
        if(buffer[pos] == c){
            pos ++;
            if(pos == size)
                isFinish = true;
        }else{
            pos = 0;
        }
    }
}