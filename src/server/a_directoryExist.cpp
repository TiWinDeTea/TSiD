#include "s_a_directoryExist.hpp"

bool a_directoryExist(Client& client){

	DIR* directory = opendir(client.path.c_str());
	std::cout << "\t-file asked: " << client.path << std::endl;
	client.packet.clear();
	
	if( directory == NULL ){

		client.packet << VoidDirectory;
		client.socket.send( client.packet );
		client.packet.clear();
		tprint();
		std::cout << client.name() << " -> file doesn't exists" << std::endl;
		return false;
	}
	
	else{
		client.packet << Exist;
		client.socket.send( client.packet );
		client.packet.clear();
		tprint();
		std::cout << client.name() << " -> file exists" << std::endl;
		return true;
	}
}