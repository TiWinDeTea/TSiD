#include "../../include/client0/moveToDirectory.hpp"

bool moveToDirectory( sf::TcpSocket& server, std::string& current_directory ){

	std::string forward_directory, previous_directory(current_directory);
	std::getline( std::cin, forward_directory );

	if( forward_directory.compare(0,1,"/") )
		current_directory += forward_directory;
	else current_directory = forward_directory;

	sf::Packet spacket;
	spacket << current_directory << Exist;
	server.send( spacket );
	spacket.clear();

	sf::Int32 answer;

	server.receive( spacket );
	if( !( spacket >> answer ) ){

		std::cout << "Couldn't retrieve server answer" << std::endl;
		return false;
	}

	if( !(interpretServerAns( static_cast<char>(answer) )) ){

		current_directory = previous_directory;
		return false;
	}

	std::cout << "Success" << std::endl;
	return true;

}
