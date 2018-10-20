/*
 * main.cpp
 *
 *  Created on: 18 ott 2018
 *      : skafo
 */
#include <iostream>

#include <netinet/in.h>

using  namespace std;

#include "man.h"
#include "client.h"


int main (int argc, char** argv){
	if(argc < 3){
		cout << "Not ehough argument! Read the man for details" << endl;
		man();
		return 0;
	}

	string hostName =argv[1];
	int portNumber= atoi(argv[2]);
	
	cout << "HOST = " << hostName << endl;
	cout << "PORT = " << portNumber << endl;

	Client *cliente = new Client(hostName,portNumber);
	cliente->handleconnection();
}
