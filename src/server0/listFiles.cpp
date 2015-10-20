#include "../../include/server0/listFiles.hpp"

bool listFiles( sf::TcpSocket& client, sf::Packet& cpacket ){
	
	//checking allowance and sending what's up about this
	
	DIR* directory = opendir(".");
	struct dirent* redfile = NULL;
	cpacket.clear();

	if( directory == NULL ){

		std::cout << "Could not open current directory" << std::endl;
		cpacket << ServerFailure;
		client.send( cpacket );
		return false;
	}//else
	
	cpacket << ServerReady;
	client.send( cpacket );
	cpacket.clear();

	while( (redfile = readdir( directory )) != NULL ){

		std::string tmp( redfile->d_name );
		
		cpacket << static_cast<unsigned int>( tmp.length() );

		for( unsigned short i(0) ; i < tmp.length() ; ++i ){
			cpacket << static_cast<sf::Int32>( redfile->d_name[i] );
		}

		client.send( cpacket );
		cpacket.clear();

	}

	cpacket << 0 << EndOfStream;
	client.send( cpacket );
	cpacket.clear(); 

	return true;
}
