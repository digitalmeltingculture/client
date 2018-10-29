/*
 * constants.h
 *
 *  Created on: 18 ott 2018
 *      Author: skafo
 */

#ifndef INCLUDE_CONSTANTS_H_
#define INCLUDE_CONSTANTS_H_

class Constants {
public:

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

	const static int MAX_BUFFER_SIZE = 1024;
	const static int NUMERIC_DATA_SIZE = 8;
	const static int CHAR_DATA_SIZE = 1;

	static const constexpr char* ERROR_SEND_INTEGER_MSG =
			"Error sendIntenger function: integer data sent failed.";
	static const constexpr char* ERROR_SEND_FLOAT_MSG =
			"Error sendFloat function: float data sent failed.";
	static const constexpr char* ERROR_SEND_DOUBLE_MSG =
			"Error sendDouble function: double data sent failed.";
	static constexpr const char* ERROR_SEND_CHAR_MSG =
			"Error sendChar function: char data sent failed.";
	static constexpr const char* ERROR_SEND_STRING_MSG =
			"Error sendString function: string data sent failed.";
	static constexpr const char* ERROR_SEND_END_CONNECTION_MSG =
				"Error sendEndConnection function: end connection  failed.";

};

#endif /* INCLUDE_CONSTANTS_H_ */
