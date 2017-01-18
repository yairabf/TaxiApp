//
// Created by hanani on 18/01/17.
//

#ifndef ADPROG1_1_INFOFORCLIENTTHREAD_H
#define ADPROG1_1_INFOFORCLIENTTHREAD_H


#include "TaxiStation.h"
#include "Server.h"

class InfoForClientThread {

private:
    int clientDescriptor;
    int* task;
    Server* server;

public:
    InfoForClientThread(int* t, Server* s);

    /**
     * getter.
     * @return the client descriptor member.
     */
    int getClientDescriptor();

    void setClientDescriptor(int client);

    /**
    * getter.
    * @return the task member.
    */
    int *getTask() const;

    /**
    * getter.
    * @return the server member.
    */
    Server *getServer() const;

};


#endif //ADPROG1_1_INFOFORCLIENTTHREAD_H
