#include <iostream>
#include "clientfiles.hpp"

void userInputInterpret( sf::TcpSocket& server, std::string user_id ){

	std::string user_input;

	do{
		std::cout << user_id << "@TSiD >";
		std::cin >> user_input;

		if( user_input == "help"){

			std::cout << "available commands :	help" << std::endl
				<< "			ls" << std::endl
				<< "			up" << std::endl
				<< "			down" << std::endl
				<< "			bye / quit / exit" << std::endl
				<< std::endl;
		}
		else if( user_input == "put" ){

			if( !sendData( server ) )
				std::cout << "Failed to upload data to server" << std::endl;
		}
		else if( user_input == "get" ){

			if( !retrieveData( server ) )
				std::cout << "Failed to retrieve data from server" << std::endl;
		}
		else if( user_input == "ls" ){

			if( !retrieveFileList( server ) )
				std::cout << "Failed to retrieve file list" << std::endl;
		}
		else if( user_input != "bye" && user_input != "exit" && user_input != "quit" ){

			std::cout << "Unknown command. Type 'help' for a list of available commands" << std::endl << std::endl;
		}

	}while( user_input != "bye" && user_input != "exit" && user_input != "quit" );

	return;
}
