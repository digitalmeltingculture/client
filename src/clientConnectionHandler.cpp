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
#include "../include/clientconnectionhandler.h"

ClientConnectionHandler::ClientConnectionHandler(string hostName, int portNumber) {
	this->hostName = hostName;
	this->portNumber = portNumber;
	this->sockFd = 0;

	initSockAddr();
}

string ClientConnectionHandler::getHostName() {
	return this->hostName;
}
int ClientConnectionHandler::getPortNumber() {
	return this->portNumber;
}
void ClientConnectionHandler::setPortNumber(int portNumber) {
	this->portNumber = portNumber;
}
void ClientConnectionHandler::setHostName(string hostName) {
	this->hostName = hostName;
}

void ClientConnectionHandler::initSockAddr() {
	memset(&clientAddress, '0', sizeof(clientAddress));

	clientAddress.sin_family = AF_INET;
	clientAddress.sin_addr.s_addr = inet_addr(hostName.c_str());
	clientAddress.sin_port = htons(portNumber);
}

ssize_t ClientConnectionHandler::handleconnection() {

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
	return sockFd;
}

/*
 Send data to the connected host
 */

//NELLA LISTA ARGOMENTI, PRIMA IL SOCK FD, poi, buff, poi type
ssize_t ClientConnectionHandler::clientSend(const void *buffer, int type, ssize_t sockfds) {
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

	size_t byteSent = -1;

	switch (type) {

		case 0:
			//end of connection
			prova = (char *) calloc(Constants::NUMERIC_DATA_SIZE, sizeof(char));
			strcat(prova, "0|");

			break;

		case 1:
			inttemp = (int *) buffer;
			chartmp = (char *) calloc(Constants::NUMERIC_DATA_SIZE, sizeof(char));
			sprintf(chartmp, "%d", *inttemp);
			prova = (char *) calloc(Constants::NUMERIC_DATA_SIZE, sizeof(char));
			strcat(prova, "4|");
			strcat(prova, chartmp);
			break;

			break;

		case 2:
			//boolean

			break;

		case 3:
			//Stringa

			inttempst = (char *) buffer;
			size_t a, b;
			a= strlen(inttempst);

			chartmp = (char *) calloc(Constants::NUMERIC_DATA_SIZE, sizeof(char));
			sprintf(chartmp, "%s", inttempst);
			prova = (char *) calloc(a, sizeof(char));
			strcat(prova, "3|");
			strcat(prova, chartmp);
			b = strlen(prova);
			cout << "lunghezza" << b << endl;
			cout << "la styringa inviata e" << prova << endl;
			break;
			break;

		case 4:
			//int
			if( ( byteSent = this->sendIntenger(buffer)) == -1)
				cout << Constants::ERROR_SEND_INTEGER << endl;

			break;

		case 5:
			//float

			inttempfl = (float *) buffer;
			chartmp = (char *) calloc(Constants::NUMERIC_DATA_SIZE, sizeof(char));
			sprintf(chartmp, "%f", *inttempfl);
			prova = (char *) calloc(8, sizeof(char));
			strcat(prova, "5|");
			strcat(prova, chartmp);
			break;
		case 8:
			//double

			inttempdb = (double *) buffer;
			chartmp = (char *) calloc(Constants::NUMERIC_DATA_SIZE, sizeof(char));
			sprintf(chartmp, "%fl", *inttempdb);
			prova = (char *) calloc(8, sizeof(char));
			strcat(prova, "8|");
			strcat(prova, chartmp);
			break;
		case 9:
			//Stringa

			inttempst = (char *) buffer;
			size_t z, y;
			z = strlen(inttempst);

			chartmp = (char *) calloc(Constants::NUMERIC_DATA_SIZE, sizeof(char));
			sprintf(chartmp, "%s", inttempst);
			prova = (char *) calloc(z, sizeof(char));
			strcat(prova, "9|");
			strcat(prova, chartmp);
			y = strlen(prova);
			cout << "lunghezza" << y << endl;
			cout << "la styringa inviata e" << prova << endl;
			break;
			//Caso default
		default:
			cout << "Tipo non ammesso" << endl;
			res = -1;
			break;

	}
//	if (send(sockfds, prova, dim, 0) < 0) {
//		perror("Send failed : ");
//		res = -1;
//	}

	return res;
}

size_t ClientConnectionHandler::sendIntenger(const void* arg){
	int *intVal = NULL;
	char *charVal = NULL, *prefix=NULL, *msg=NULL;
	intVal = (int*)arg;

	size_t byteSent = -1;
	size_t msgSize = 2*Constants::NUMERIC_DATA_SIZE + 2;

	charVal = (char *) calloc(Constants::NUMERIC_DATA_SIZE +1, sizeof(char));
	prefix  = (char *) calloc(Constants::NUMERIC_DATA_SIZE +2, sizeof(char));
	msg  	= (char *) calloc(msgSize, sizeof(char));

	sprintf(charVal, "%d", *intVal);
	sprintf(prefix, "%d", Constants::INTEGER);

	strcat(prefix, "|");
	strcat(msg,prefix);
	strcat(msg,charVal);

	byteSent = send(this->sockFd, msg, msgSize, 0);

	cout << "MSG = " << msg << ". Byte: " << byteSent << endl;
	free(charVal);
	free(prefix);
	free(msg);

	return byteSent;
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
