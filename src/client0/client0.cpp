#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include "clientfiles.hpp"
#include "../common/commonfiles.hpp"

bool sconnect( sf::TcpSocket& socket ) {								//Connect the client to the server

	unsigned short remote_port;
	std::string remote_address;

	std::cout << "Remote address : ";
	std::cin >> remote_address;
	std::cout << "Remote port : ";
	std::cin >> remote_port;
	std::cout << "Connecting to the remote @ " << remote_address << ":" << remote_port << std::endl;

	if( socket.connect( remote_address, remote_port ) != sf::Socket::Done ){
		std::cout << "Connection wasn't successful" << std::endl;
		return false;
	}

	std::cout << "Successfully connected" << std::endl;
	return true;
}

int main(int argc, char* argv[]) {

	sf::TcpSocket socket;
	std::string user_input;

	if( !sconnect( socket ) )
			return 1;

	do{
		std::cout << ">";
		std::cin >> user_input;

		if( user_input == "help"){

			std::cout << "available commands : help — ls — up — down — q" << std::endl;
		}
		else if( user_input == "up" ){

			if( !sendData( socket ) )
				std::cout << "Failed to upload data to server" << std::endl;
		}
		else if( user_input == "down" ){

			if( !retrieveData( socket ) )
				std::cout << "Failed to retrieve data from server" << std::endl;
		}
		else if( user_input == "ls" ){

			if( !retrieveFileList( socket ) )
				std::cout << "Failed to retrieve file list" << std::endl;
		}
		else if( user_input != "q" ){

			std::cout << "Unknown command. Type 'help' for a list of available commands" << std::endl << std::endl;
		}

	}while( user_input != "q" );

	sf::Packet bye;
	bye << Disconnect;
	socket.send( bye );

	socket.disconnect();
	return EXIT_SUCCESS;
}
