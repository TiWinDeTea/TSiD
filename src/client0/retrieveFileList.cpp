#include <iostream>
#include <SFML/Network.hpp>
#include "../common/commonfiles.hpp"


bool retrieveFileList( sf::TcpSocket& server ){

	sf::Packet spacket;
	
	spacket << Ls;
	server.send( spacket );
	spacket.clear();

	sf::Int8 file;
	unsigned int filename_length;

	server.receive( spacket );
	spacket >> file;
	spacket.clear();

	if( static_cast<char>(file) == ServerFailure ){
		std::cout << "ServerFailure" << std::endl;
		return false;
	}

	do{
		server.receive( spacket );
		
		spacket >> filename_length;
		for( unsigned int i(0) ; i < 4*filename_length ; ++i){

			spacket >> file;
			std::cout << static_cast<char>(file);
		}
		std::cout << std::endl;
		spacket.clear();

	}while( filename_length != 0);

	return true;
}
