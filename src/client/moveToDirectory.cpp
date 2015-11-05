#include "c_moveToDirectory.hpp"

bool moveToDirectory( sf::TcpSocket& server, std::string& current_directory ){

	std::string forward_directory(""), previous_directory(current_directory);
	std::cin.ignore();
	std::getline( std::cin, forward_directory);

	while( !forward_directory.compare(0,2,"./") )
		forward_directory.erase( 0, 2 );

	size_t working_pos( forward_directory.find( "//" ) );

	while( working_pos != std::string::npos ){

		forward_directory.erase( working_pos, 1 );
		working_pos = forward_directory.find( "//");
	}

	if( forward_directory == "." || forward_directory == "")
		return true;

	if( forward_directory.compare(0,1,"/") )
		current_directory += forward_directory + "/";
	else current_directory = forward_directory + "/";

	formatDir(current_directory);

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

	return true;
}
