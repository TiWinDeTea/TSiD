#include "../../include/client0/createDirectory.hpp"

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
	int s_ans;
	spacket >> s_ans;

	return interpretServerAns( static_cast<char>(s_ans) );
}
