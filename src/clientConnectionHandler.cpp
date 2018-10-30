/*
 * client.cpp
 *
 *  Created on: 18 ottho 2018
 *      Author: sksasafo
 */

#include <iostream>

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

using namespace std;

#include "constants.h"
#include "../include/clientconnectionhandler.h"

ClientConnectionHandler::ClientConnectionHandler(string hostName,
		int portNumber) {
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
ssize_t ClientConnectionHandler::clientSend(const void *buffer, int type,
		ssize_t sockfds) {
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
cout <<"Client Send"<<endl;
	switch (type) {

	case 0:
		//end of connection
		if ((byteSent = this->sendClose(buffer)) == -1)
				cout << Constants::ERROR_SEND_END_CONNECTION_MSG << endl;

			break;

	case 1:
		// byte
//		if ((byteSent = this->sendByte(buffer)) == -1)
//				cout << Constants::ERROR_SEND_INTEGER << endl;

			break;

	case 2:
		//boolean

		break;

	case 3:
		//Carattere

		if ((byteSent = this->sendChar(buffer)) == -1)
			cout << Constants::ERROR_SEND_CHAR_MSG << endl;

		break;
	case 4:
		//int

		if ((byteSent = this->sendIntenger(buffer)) == -1)
			cout << Constants::ERROR_SEND_INTEGER_MSG << endl;

		break;
	case 5:
		//float

		if ((byteSent = this->sendFloat(buffer)) == -1)
			cout << Constants::ERROR_SEND_FLOAT_MSG << endl;

		break;
	case 8:
		//double

		if ((byteSent = this->sendDouble(buffer)) == -1)
			cout << Constants::ERROR_SEND_DOUBLE_MSG << endl;

		break;
	case 9:
		//Stringa
		if ((byteSent = this->sendString(buffer)) == -1)
			cout << Constants::ERROR_SEND_STRING_MSG << endl;

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

//Function send integer

size_t ClientConnectionHandler::sendIntenger(const void* arg) {
	int *intVal = NULL;
	char *charVal = NULL, *prefix = NULL, *msg = NULL;
	intVal = (int*) arg;

	ssize_t byteSent = -1;
	size_t msgSize = 2 * Constants::NUMERIC_DATA_SIZE + 2;

	charVal = (char *) calloc(Constants::NUMERIC_DATA_SIZE + 1, sizeof(char));
	prefix = (char *) calloc(Constants::NUMERIC_DATA_SIZE + 2, sizeof(char));
	msg = (char *) calloc(msgSize, sizeof(char));

	sprintf(charVal, "%d", *intVal);
	sprintf(prefix, "%d", Constants::INTEGER);

	strcat(prefix, "|");
	strcat(msg, prefix);
	strcat(msg, charVal);

	sleep(5);
	byteSent = send(this->sockFd, msg, msgSize, 0);

	cout << "MSG = " << msg << ". Byte: " << byteSent << endl;
	free(charVal);
	free(prefix);
	free(msg);

	sleep(5);

	return byteSent;
}

//Function send Float

size_t ClientConnectionHandler::sendFloat(const void* arg) {
	float *intVal = NULL;
	char *charVal = NULL, *prefix = NULL, *msg = NULL;
	intVal = (float*) arg;

	size_t byteSent = -1;
	size_t msgSize = 2 * Constants::NUMERIC_DATA_SIZE + 2;

	charVal = (char *) calloc(Constants::NUMERIC_DATA_SIZE + 1, sizeof(char));
	prefix = (char *) calloc(Constants::NUMERIC_DATA_SIZE + 2, sizeof(char));
	msg = (char *) calloc(msgSize, sizeof(char));

	sprintf(charVal, "%f", *intVal);
	sprintf(prefix, "%d", Constants::FLOAT);

	strcat(prefix, "|");
	strcat(msg, prefix);
	strcat(msg, charVal);

	byteSent = send(this->sockFd, msg, msgSize, 0);

	cout << "MSG = " << msg << ". Byte: " << byteSent << endl;
	free(charVal);
	free(prefix);
	free(msg);

	return byteSent;
}

//Function send Double

size_t ClientConnectionHandler::sendDouble(const void* arg) {
	double *intVal = NULL;
	char *charVal = NULL, *prefix = NULL, *msg = NULL;
	intVal = (double*) arg;

	size_t byteSent = -1;
	size_t msgSize = 2 * Constants::NUMERIC_DATA_SIZE + 2;

	charVal = (char *) calloc(Constants::NUMERIC_DATA_SIZE + 1, sizeof(char));
	prefix = (char *) calloc(Constants::NUMERIC_DATA_SIZE + 2, sizeof(char));
	msg = (char *) calloc(msgSize, sizeof(char));

	sprintf(charVal, "%lf", *intVal);
	sprintf(prefix, "%d", Constants::DOUBLE);

	strcat(prefix, "|");
	strcat(msg, prefix);
	strcat(msg, charVal);

	byteSent = send(this->sockFd, msg, msgSize, 0);

	cout << "MSG = " << msg << ". Byte: " << byteSent << endl;
	free(charVal);
	free(prefix);
	free(msg);

	return byteSent;
}

 //Function send Byte

size_t ClientConnectionHandler::sendByte(const void* arg) {
	int *intVal = NULL;
	char *charVal = NULL, *prefix = NULL, *msg = NULL;
	intVal = (int*) arg;

	size_t byteSent = -1;
	size_t msgSize = 2 * Constants::NUMERIC_DATA_SIZE + 2;

	charVal = (char *) calloc(Constants::NUMERIC_DATA_SIZE + 1, sizeof(char));
	prefix = (char *) calloc(Constants::NUMERIC_DATA_SIZE + 2, sizeof(char));
	msg = (char *) calloc(msgSize, sizeof(char));

	sprintf(charVal, "%d", *intVal);
	sprintf(prefix, "%d", Constants::FLOAT);

	strcat(prefix, "|");
	strcat(msg, prefix);
	strcat(msg, charVal);

	byteSent = send(this->sockFd, msg, msgSize, 0);

	cout << "MSG = " << msg << ". Byte: " << byteSent << endl;
	free(charVal);
	free(prefix);
	free(msg);

	return byteSent;
}

//Function send Char

size_t ClientConnectionHandler::sendChar(const void* arg) {
	int *intVal = NULL;
	char *charVal = NULL, *prefix = NULL, *msg = NULL;
	intVal = (int*) arg;

	size_t byteSent = -1;
	size_t msgSize = 2 * Constants::CHAR_DATA_SIZE + 2;

	charVal = (char *) calloc(Constants::CHAR_DATA_SIZE + 1, sizeof(char));
	prefix = (char *) calloc(Constants::CHAR_DATA_SIZE + 2, sizeof(char));
	msg = (char *) calloc(msgSize, sizeof(char));

	sprintf(charVal, "%d", *intVal);
	sprintf(prefix, "%d", Constants::CHAR);

	strcat(prefix, "|");
	strcat(msg, prefix);
	strcat(msg, charVal);

	byteSent = send(this->sockFd, msg, msgSize, 0);

	cout << "MSG = " << msg << ". Byte: " << byteSent << endl;
	free(charVal);
	free(prefix);
	free(msg);

	return byteSent;
}

//Function send String

size_t ClientConnectionHandler::sendString(const void* arg) {
	char *intVal = NULL;
	char *charVal = NULL, *prefix = NULL, *msg = NULL;
	intVal = (char*) arg;
	int dim;

	size_t byteSent = -1;
	size_t msgSize = 2 * dim *Constants::CHAR_DATA_SIZE + 2;
	dim=strlen(intVal);
	charVal = (char *) calloc(dim*Constants::CHAR_DATA_SIZE + 1, sizeof(char));
	prefix = (char *) calloc(dim*Constants::CHAR_DATA_SIZE + 2, sizeof(char));
	msg = (char *) calloc(msgSize, sizeof(char));

	sprintf(charVal, "%d", *intVal);
	sprintf(prefix, "%d", Constants::STRING);

	strcat(prefix, "|");
	strcat(msg, prefix);
	strcat(msg, charVal);

	byteSent = send(this->sockFd, msg, msgSize, 0);

	cout << "MSG = " << msg << ". Byte: " << byteSent << endl;
	free(charVal);
	free(prefix);
	free(msg);

	return byteSent;
}

//Function send END CONNECTION

size_t ClientConnectionHandler::sendClose(const void* arg) {
	int *intVal = NULL;
	char *charVal = NULL, *prefix = NULL, *msg = NULL;
	intVal = (int*) arg;

	size_t byteSent = -1;
	size_t msgSize = 2 * Constants::CHAR_DATA_SIZE + 2;

	charVal = (char *) calloc(Constants::CHAR_DATA_SIZE + 1, sizeof(char));
	prefix = (char *) calloc(Constants::CHAR_DATA_SIZE + 2, sizeof(char));
	msg = (char *) calloc(msgSize, sizeof(char));

	sprintf(charVal, "%d", *intVal);
	sprintf(prefix, "%d", Constants::END_CONNECTION);

	strcat(prefix, "|");
	strcat(msg, prefix);
	strcat(msg, charVal);

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
