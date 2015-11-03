#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include "../../include/client0/userInputInterpret.hpp"
#include "../../include/common/setStdcinEcho.hpp"
#include "../../include/client0/serverAnsInterpret.hpp"
#include "../../include/common/setColors.hpp"

bool sconnect( sf::TcpSocket& socket, std::string& user_id ) {								//Connect the client to the server

	unsigned short remote_port;
	std::string remote_address, user_pass;

	std::cout << "User ID : ";
	std::cin >> user_id;

	std::cout << "User passwd : ";
	setStdcinEcho( false );
	std::cin.ignore();
	std::getline(std::cin, user_pass);
	setStdcinEcho( true );


	std::cout << std::endl << "Remote address : ";
	std::cin >> remote_address;
	std::cout << "Remote port : ";
	std::cin >> remote_port;
	std::cout << "Connecting to the remote @ " << remote_address << ":" << remote_port << std::endl;

	if( socket.connect( remote_address, remote_port ) != sf::Socket::Done ){
		std::cout << "Connection wasn't successful" << std::endl;
		return false;
	}

	std::cout << "Connected to server" << std::endl;

	sf::Packet user;
	user << user_id << user_pass;
	socket.send( user );
	user.clear();

	int id_state;
	socket.receive( user );
	user >> id_state;

	return interpretServerAns( static_cast<char>(id_state) );
}

int main() {

	setColors("reset");

	sf::TcpSocket socket;
	std::string user_id;

	if( !sconnect( socket, user_id ) )
		return 1;

	userInputInterpret( socket, user_id );

	sf::Packet bye;
	bye << "" << Disconnect;
	socket.send( bye );

	socket.disconnect();

	return EXIT_SUCCESS;
}
