#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include "clientfiles.hpp"
#include "../common/commonfiles.hpp"

bool sconnect( sf::TcpSocket& socket, std::string& user_id ) {								//Connect the client to the server

	unsigned short remote_port;
	std::string remote_address;

	std::cout << "User ID : ";
	std::cin >> user_id;

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

int main() {

	sf::TcpSocket socket;
	std::string user_id;

	if( !sconnect( socket, user_id ) )
		return 1;

	userInputInterpret( socket, user_id );

	sf::Packet bye;
	bye << Disconnect;
	socket.send( bye );

	socket.disconnect();

	return EXIT_SUCCESS;
}
