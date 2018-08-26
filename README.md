# Pipe Stream Merge

## Goals
This Application has the goal to combine the data stream of of several ingoing data-streams to one (planed : several identically) outgoing data-stream. 
In order to do this, it links all ingoing named-pipes or SSH data-streams to one outgoing named pipe.
This is necessary if you have
  - several remote connections/data-Streams ( SSH, serial, ...) where the ingoing traffic should be combined
  - several apps whose transmitted data should be combined to one pipe

This application is the bases off Pcap-Relay which has been written to enable sniffing with several remote Clients. 
Each Client sends its tcpdump via ssh to a named pipe at the host system.
All named pipes are joined to one outgoing pipe witch can be read by Wireshark or Foren6 (XXXX generell: Wann ein Punkt am Ende, wann nicht?)
   
It also is possible to use an embedded ssh connection (uses the cli ssh commands of the host system). Here you can 
connect to several remote clients and transfer a remote command. After executed its data/content will be send to the host computer. 


![Alt text](structimg.png?raw=true "structure")

***
## How to use
start the programm from the cli. 
you can user these parameter:
            
               -ssh     <configFile>
               -pipe    <numberOf>
               -l       <outPutLocation>        	default : /tmp/pipeRelay 
               -log     <loglevel>                  Degree of detailedness of the application`s report default:0 max:4 
               <no paramether>                  	2 named pipes


            
   < configFile > is the name and/or the location of the file witch describe the ssh connection.  
    
   < number of > is the number of named pipes which the programm should open.     
   The named pipes are stored at "/tmp/pipeRelay< number >"
   if there is no parameter the application create per default 3 named-pipes.    
   
   "encap"sulation: linux encapsulates network packages from an unknown source. Foren6 is not able to handle such Packages
   the solution in this case is to remove this encapsulation header and change the pcap-linklayer to a 6lowpan one.
   By default this feature is enabled.
   
 ### Config-File
If the application runs in ssh mode, the user has to define a config file. Using this file the app can read which clients to 
connect to and which applications are supposed to run at the remote client.   
The config file has following definitions:   
- each entry stands in a separate line
- a space (' ') separates the entry-parts
- an empty line or the EOF descriptor define the end of the config file 
- there are max 200 chars allowed per line   

#### Syntax:   
* < hostname or ip> < space> < username> < space> < remote command>    <line end>

* < hostname or ip> < space> < username> < space> < remote command>   <line end>

* ...   
   
e.g   

          127.0.0.1 linuxUser sudo tcpdump -i eth0
          myServer  sudo tcpdump -i eth0  // invalid          
          8.8.8.8 google please hack that for me :)   
          
* the first line says that the host ist "127.0.0.1" the user is "LinuxUser" and the command is "sudo tcpdump -i eth0"   
* the second line says that the host ist "myServer" the user is empty(2 spaces)   and the command is "tcpdump -i eth0"    
* the third line says that the end of the config is reached so that the entry in the fourth line will be ignored     
   
***
***
## How to dev 

-   Each Pipe Reader shall run in a single Thread. 
-   All pipe-reader obj shall have the same outgoing pipe obj
   
## Function   

### main
The main function can be called either with no or with two parameters.   
If there is no parameter the program will by default create 3 named pipes at "/tmp/pipeRelay< 0-2>   
by using the parameter ["pipe"],[< number >]  the program will create < number> pipes at "/tmp/pipeRelay[0-(number-1)]   
If the parameter is ["ssh"],["name"] the program will use a ssh connection to the clients name. For this purpose the name of the config file
  describes the name of the client the host is supposed to connect to.   
   
### Reader
Pipereader is the reading part of this application. 
Each reader shall run in an single thread 
-Constructor
     
        reader(location, writer, name, message, log)
            string *location    : location of the named pipe               default : "/tmp/pipeRelayOut"
            writer *writer      : outgoing obj (each obj shall have the same)
            string *name        : identifier in log and messages           default : "unnamed reader"
                                         
        
- open()   
    After creating the reader obj the main application has to run the open() method 
    This method creates a named pipe at <location> (and deletes the old file if existent)
    open() blocks until a write app opens the other end of the named pipe
    
- read(char * buff, int size)   
   reads < size > bytes from the ingoing pipe and writes them to the given buffer
 
### Writer
Pipewriter is the writing part of this application.
There is only one writer. 
Each reader thread sends its pcap data to this writer. The methods writer (pcap) and write (byte[], size) are 
protected by an mutex, which prevents simultaneous writing by differned threads 
-   Constructor

        writer(location, name , message, log)
            string *location    : location of the named pipe                default : "/tmp/pipeRelayOut"
            string *name        : identifier in log and messages            default : "unnamed writer"
        
-   open()   
        After creating the writer obj the application has to open the writer
        this method creates a named pipe at <location> (and deletes the old on if existent)
        open() blocks until the reading end of the named pipe gets opend
-   write(char * byte , size)   
        Write a byte array to the pipe
        this method uses mutex to avoid simultaneous writings
        
  

 
### SSH
This application supports an embedded ssh connection to the remote host (using the default ssh program on your client pc).   
For this purpose it is necessary to be able to login passwordless at the remote client by using e.g a keyfile.   
The user has to tell the application  which clients to connect to by an config file.  
Some applications at the remote client must run as root.
To avoid password leaks in config files it is recommended to add the application to the "visudo" list. This enables that the application 
does not request an sudo password.   
Alternatively, you can use an keypass program (in the config file).   
   
The embedded ssh connection has lots of overhead at the beginning. Therefor the run method first checks the 
pcap signature and then reads as long as there is no signature.   
The main usage will be tcpdump. run() will checks for the tcpdump signature and cuts it out.
    
    ssh(host, user, remoteExecute, *outPipe)
    or
    ssh(ReadConfig::entry *inputEntry, *outPipe) 
    
        string host                    :     IP-Address or the host name 
        string user                    :     user name on the remote machine
        string remoteExecute:          :     command that will be executed on the remote machine 
        ReadConfig::entry *inputEntry  :     struct created by the config reader
        writer *outPipe                :     outgoing pipeWriter. The ssh obj send its pcap to this class

* bool open()   
opens the ssh conection    
  
* void run()    
Starts the ssh loop. At first it cuts out all ssh related overhead. Thereafter it sends the pcap-file-header to the outgoing pipe 
and starts reading pcaps

* read(char * buff, int size)   
   reads < size > bytes from the ingoing pipe and writes them to the given buffer
 
