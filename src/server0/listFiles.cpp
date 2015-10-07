#include <SFML/Network.hpp>
#include <dirent.h>
#include <iostream>
#include "../common/commonfiles.hpp"

#ifndef WIN32
	#include <sys/types.h>
#endif

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
	}
	
	cpacket << ServerReady;
	client.send( cpacket );
	cpacket.clear();

	std::string file_name;

	while( (redfile = readdir( directory )) != NULL ){

		file_name = redfile->d_name;
		
		cpacket << static_cast<unsigned int>(file_name.length());

		std::cout << "Length : " << file_name.length() << std::endl;

		for( unsigned short i(0) ; i < file_name.length() ; ++i ){
			cpacket << file_name[i];
			std::cout << file_name[i];
		}
		std::cout << std::endl;

		client.send( cpacket );
		cpacket.clear();

	}

	cpacket << 0 << EndOfStream;
	client.send( cpacket );
	cpacket.clear(); 

	return true;
}
