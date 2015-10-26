#include "../../include/server0/listFiles.hpp"

bool listFiles(Client& client){
	
	//checking allowance and sending what's up about this
	
	DIR* directory = opendir(client.path.c_str());
	struct dirent* redfile = NULL;
	client.packet.clear();

	if( directory == NULL ){

		client.packet << VoidDirectory;
		client.socket.send( client.packet );
		tcout() << client.name() << " -> Could not open the directory" << std::endl;
		return false;
	}//else
	
	client.packet << ServerReady;
	client.socket.send( client.packet );
	client.packet.clear();
	tcout() << client.name() << " -> Server ready to list" << std::endl;

	if(client.path == "./Public/"){

		client.packet << 8 
		<< static_cast<sf::Int32>('P')
		<< static_cast<sf::Int32>('r')
		<< static_cast<sf::Int32>('i')
		<< static_cast<sf::Int32>('v')
		<< static_cast<sf::Int32>('a')
		<< static_cast<sf::Int32>('t')
		<< static_cast<sf::Int32>('e')
		<< static_cast<sf::Int32>('/');
		client.socket.send( client.packet );
		client.packet.clear();
	}

	while( (redfile = readdir( directory )) != NULL ){

		std::string tmp( redfile->d_name );

		if( isFolder(client.path + tmp) ){
			tmp += "/";
		}
		
		client.packet << static_cast<unsigned int>( tmp.length() );

		for( unsigned short i(0) ; i < tmp.length() ; ++i ){
			client.packet << static_cast<sf::Int32>( tmp[i] );
		}

		client.socket.send( client.packet );
		client.packet.clear();

	}

	client.packet << 0 << EndOfStream;
	client.socket.send( client.packet );
	client.packet.clear(); 
	tcout() << client.name() << " -> file listed" << std::endl;

	return true;
}
