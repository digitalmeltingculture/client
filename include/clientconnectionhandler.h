/*
 * client.h
 *
 *  Created on: 18 ott 2018
 *      Author: skafo
 */

#ifndef CLIENT_H_
#define CLIENT_H_

class ClientConnectionHandler {

private:
	struct sockaddr_in clientAddress;
	string hostName;
	int portNumber;
	int sockFd;

public:
	ClientConnectionHandler(string, int);

	void initSockAddr();
	ssize_t handleconnection();

	string getHostName();
	int getPortNumber();
	ssize_t sockfds;

	void setHostName(string);
	void setPortNumber(int);
	string receive(int, int);
	ssize_t clientSend(const void *, int, ssize_t);

	size_t sendIntenger(const void*);
	size_t sendFloat(const void*);
	size_t sendDouble(const void*);
	size_t sendByte(const void*);
	size_t sendChar(const void*);
	size_t sendString(const void*);
	size_t sendClose(const void*);
};

#endif /* CLIENT_H_ */
