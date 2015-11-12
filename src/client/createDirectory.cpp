#include "c_createDirectory.hpp"

bool createDirectory( sf::TcpSocket& server, std::string const& current_directory ){

	std::cin.ignore();
	std::string folder_name;
	std::getline( std::cin, folder_name );
	
	sf::Packet spacket;
	spacket.clear();
	spacket << current_directory + folder_name << Mkdir;
	server.send( spacket );
	spacket.clear();

	server.receive( spacket );
	sf::Int32 s_ans;

	if( !(spacket >> s_ans) ){

		std::cout << "Could not retrieve server state" << std::endl;
		return false;
	}

	return interpretServerAns( static_cast<char>(s_ans) );
}
