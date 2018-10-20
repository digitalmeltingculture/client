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

#include "constants.h"
#include "client.h"

Client::Client(string hostName, int portNumber) {
	this->hostName = hostName;
	this->portNumber = portNumber;
	this->sockFd = 0;

	initSockAddr();
}

string Client::getHostName() {
	return this->hostName;
}
int Client::getPortNumber() {
	return this->portNumber;
}
void Client::setPortNumber(int portNumber) {
	this->portNumber = portNumber;
}
void Client::setHostName(string hostName) {
	this->hostName = hostName;
}

void Client::initSockAddr() {
	memset(&clientAddress, '0', sizeof(clientAddress));

	clientAddress.sin_family = AF_INET;
	clientAddress.sin_addr.s_addr = inet_addr(hostName.c_str());
	clientAddress.sin_port = htons(portNumber);
}

int Client::handleconnection() {

	struct sockaddr_in address;
	int valread;
	struct sockaddr_in serv_addr;

	if ((sockFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	if (connect(sockFd, (struct sockaddr *) &clientAddress,
			sizeof(clientAddress)) < 0) {
		cout << hostName.c_str() << endl;
		printf("\nConnection Failed \n");
		return -1;
	}
	return 0;
}

/**
 Send data to the connected host
 */

ssize_t Client::send(const void *buffer, int type) {
	ssize_t res;
	size_t dim;
	const void *strbuffer;
	char msg[2];
	int *inttemp;
	char *chartmp;
	char *prova;
	float *inttempfl;
	double *inttempdb;
	const char *inttempst;

	//Send some data
	/*if( send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
	 {
	 perror("Send failed : ");
	 return false;
	 }
	 cout<<"Data send\n";

	 return true;
	 */
	switch (type) {

	case 0:
		//end of connection
		prova = (char *) calloc( Constants::BUFFER_DIMENSION, sizeof(char));
		strcat(prova, "0|");

		break;

	case 1:
		//byte

		break;

	case 2:
		//boolean

		break;

	case 3:
		//char

		break;

	case 4:
		//int

		inttemp = (int *) buffer;
		chartmp = (char *) calloc( Constants::BUFFER_DIMENSION, sizeof(char));
		sprintf(chartmp, "%d", *inttemp);
		prova = (char *) calloc( Constants::BUFFER_DIMENSION, sizeof(char));
		strcat(prova, "4|");
		strcat(prova, chartmp);
		break;

	case 5:
		//float

		inttempfl = (float *) buffer;
		chartmp = (char *) calloc( Constants::BUFFER_DIMENSION, sizeof(char));
		sprintf(chartmp, "%f", *inttempfl);
		prova = (char *) calloc(8, sizeof(char));
		strcat(prova, "5|");
		strcat(prova, chartmp);
		break;
	case 8:
		//double

		inttempdb = (double *) buffer;
		chartmp = (char *) calloc( Constants::BUFFER_DIMENSION, sizeof(char));
		sprintf(chartmp, "%fl", *inttempdb);
		prova = (char *) calloc(8, sizeof(char));
		strcat(prova, "8|");
		strcat(prova, chartmp);
		break;
	case 9:
		//Stringa

		inttempst = (char *) buffer;
		size_t z;
		z = strlen(inttempst);

		chartmp = (char *) calloc( Constants::BUFFER_DIMENSION, sizeof(char));
		sprintf(chartmp, "%s", inttempst);
		prova = (char *) calloc(z, sizeof(char));
		strcat(prova, "9|");
		strcat(prova, chartmp);

		break;
		//Caso default
	default:
		cout << "Tipo non ammesso" << endl;
		res = -1;
		break;

	}
	/*if (send(sockFd, buffer, dim, 0) < 0) {
	 perror("Send failed : ");
	 res = -1;
	 }*/
	return res;
}

/**
 Receive data from the connected host
 */
/*string Client::receive(int size = 512, int sock) {
 char buffer[size];
 string reply;

 //Receive a reply from the server
 if (recv(sock, buffer, sizeof(buffer), 0) < 0) {
 puts("recv failed");
 }

 reply = buffer;
 return reply;
 }*/
