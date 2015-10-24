#include "../../include/server0/listFiles.hpp"

bool listFiles(Client& client){
	
	//checking allowance and sending what's up about this
	
	DIR* directory = opendir(client.path.c_str());
	struct dirent* redfile = NULL;
	client.packet.clear();

	if( directory == NULL ){

		client.packet << VoidDirectory;
		client.socket.send( client.packet );
		std::cout << client.name() << " -> Could not open the directory" << std::endl;
		return false;
	}//else
	
	client.packet << ServerReady;
	client.socket.send( client.packet );
	client.packet.clear();
	std::cout << client.name() << " -> Server ready to list" << std::endl;

	while( (redfile = readdir( directory )) != NULL ){

		std::string tmp( redfile->d_name );
		
		client.packet << static_cast<unsigned int>( tmp.length() );

		for( unsigned short i(0) ; i < tmp.length() ; ++i ){
			client.packet << static_cast<sf::Int32>( redfile->d_name[i] );
		}

		client.socket.send( client.packet );
		client.packet.clear();

	}

	client.packet << 0 << EndOfStream;
	client.socket.send( client.packet );
	client.packet.clear(); 
	std::cout << client.name() << " -> file listed" << std::endl;

	return true;
}
