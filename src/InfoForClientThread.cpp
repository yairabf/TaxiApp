//
// Created by hanani on 18/01/17.
//

#include "InfoForClientThread.h"

InfoForClientThread::InfoForClientThread(int* t, Server* s) {
    task = t;
    server = s;
}

int InfoForClientThread::getClientDescriptor() {
    return clientDescriptor;
}

int *InfoForClientThread::getTask() const {
    return task;
}

Server *InfoForClientThread::getServer() const {
    return server;
}

void InfoForClientThread::setClientDescriptor(int client) {
    clientDescriptor = client;
}
