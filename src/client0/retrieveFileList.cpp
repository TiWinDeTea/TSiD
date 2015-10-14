#include "../../include/client0/retrieveFileList.hpp"


bool retrieveFileList( sf::TcpSocket& server ){

	sf::Packet spacket;
	
	spacket << Ls;
	server.send( spacket );
	spacket.clear();

	sf::Int32 file;
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
		for( unsigned int i(0) ; i < filename_length ; ++i ){

			spacket >> file;
			std::wcout << static_cast<wchar_t>( file );
		}
		std::cout << std::endl;
		spacket.clear();

	}while( filename_length != 0 );

	return true;
}
