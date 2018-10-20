/*
 * client.h
 *
 *  Created on: 18 ott 2018
 *      Author: skafo
 */

#ifndef CLIENT_H_
#define CLIENT_H_

class Client{

private:
	struct sockaddr_in clientAddress;
	string hostName;
	int portNumber;
	int sockFd;

public :
	Client(string,int);

	void initSockAddr();
	int handleconnection();

	string getHostName();
	int getPortNumber();

	void setHostName(string);
	void setPortNumber(int);

};



#endif /* CLIENT_H_ */
