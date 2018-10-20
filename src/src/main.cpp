/*
 * main.cpp
 *
 *  Created on: 18 ott 2018
 *      : skafo
 */
#include <iostream>

using  namespace std;

#include <cstdio>

#include <stdlib.h>

#include <netinet/in.h>


#include "man.h"

#include "constants.h"

#include "client.h"


int main (int argc, char** argv){
	if(argc < 3){
		cout << "Not ehough argument! Read the man for details" << endl;
		man();
		return 0;
	}

	string hostName =argv[1];
	int portNumber= atoi(argv[2]);
	char *temp;
	char tmp [8];

	char  a []="finale";
	
	cout << "HOST = " << hostName << endl;
	cout << "PORT = " << portNumber << endl;

	Client *cliente = new Client(hostName,portNumber);

	cliente->send(&a,9);

	cliente->handleconnection();
}
