/*
 * client.cpp
 *
 *  Created on: 18 ottho 2018
 *      Author: sksasafo
 */


#include <iostream>

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

using namespace std;

#include "client.h"


Client::Client(string hostName,int portNumber){
	this->hostName=hostName;
	this->portNumber=portNumber;
	this->sockFd=0;

    initSockAddr();
}

string Client::getHostName(){
	return this->hostName;
}
int Client::getPortNumber(){
	return this->portNumber;
}
void Client::setPortNumber(int portNumber){
	this->portNumber=portNumber;
}
void Client::setHostName(string hostName){
	this->hostName=hostName;
}

void Client::initSockAddr(){
    memset(&clientAddress, '0', sizeof(clientAddress));

    clientAddress.sin_family = AF_INET;
    clientAddress.sin_addr.s_addr = inet_addr( hostName.c_str());
    clientAddress.sin_port = htons(portNumber );
}

int Client::handleconnection(){

    struct sockaddr_in address;
    int valread;
    struct sockaddr_in serv_addr;

    if ((sockFd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("\n Socket creation error \n");
        return -1;
    }

    if (connect(sockFd, (struct sockaddr *)&clientAddress, sizeof(clientAddress)) < 0){
        cout << hostName.c_str()<< endl;
        printf("\nConnection Failed \n");
        return -1;
    }
    return 0;
}
