/*
 * main.cpp
 *
 *  Created on: 18 ott 2018
 *      : skafo
 */
#include <iostream>

using namespace std;

#include <cstdio>
#include <stdlib.h>
#include <netinet/in.h>
#include <limits.h>

#include "man.h"
#include "constants.h"
#include "clientconnectionhandler.h"

int main(int argc, char** argv) {
	if (argc < 3) {
		cout << "Not ehough argument! Read the man for details" << endl;
		man();
		return 0;
	}

	string hostName = argv[1];
	int portNumber = atoi(argv[2]);
	char *temp;
	char tmp[8];
	ssize_t risp, sockfds;

	cout << "HOST = " << hostName << endl;
	cout << "PORT = " << portNumber << endl;

	ClientConnectionHandler *cliente = new ClientConnectionHandler(hostName, portNumber);

	sockfds = cliente->handleconnection();

	int tmpInt = INT_MAX;
	int tmpInt2 = 0;
	risp = cliente->clientSend(&tmpInt, Constants::INTEGER, sockfds);
	risp = cliente->clientSend(&tmpInt2, Constants::END_CONNECTION, sockfds);
	cout << "ecco il ris" << risp << endl;
	cout << "il socket" << sockfds << endl;



}
