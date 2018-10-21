/*
 * constants.h
 *
 *  Created on: 18 ott 2018
 *      Author: skafo
 */

#ifndef INCLUDE_CONSTANTS_H_
#define INCLUDE_CONSTANTS_H_

class Constants{
	public:
		const static int MAX_BUFFER_SIZE = 1024;
		const static int SMALL_BUFFER_SIZE = 128;
		const static int NUMERIC_BUFFER_SIZE = 8;

		const static int DEFAULT_PORT_NUMBER = 8080;
		const static int MAX_CONNECTIONS_NUMBER = 5;

		const static int END_CONNECTION = 0;
		const static int BYTE = 1;
		const static int BOOLEAN = 2;
		const static int CHAR = 3;
		const static int INTEGER = 4;
		const static int FLOAT = 5;
		const static int DOUBLE = 8;
		const static int STRING = 9;

		static constexpr const char* ERROR_MSG_SEND_TO_SERVER = "Error in sending data to server";

		static constexpr const char* ERROR_MSG_SEND_INTEGER	  = "Error in sending integer data";
		static constexpr const char* ERROR_MSG_SEND_STRING	  = "Error in sending string data";

};

#endif /* INCLUDE_CONSTANTS_H_ */
