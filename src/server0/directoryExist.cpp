#include "../../include/server0/directoryExist.hpp"

void directoryExist(Client& client){

	DIR* directory = opendir(client.path.c_str());
	if( directory == NULL ){

		std::cout << client.name() << ": " <<client.path << " doesn't exist" << std::endl;
		client.packet << VoidDirectory;
		client.socket.send( client.packet );
	}
	else{
		std::cout << client.name() << ": " <<client.path << " exist" << std::endl;
		client.packet << Exist;
		client.socket.send( client.packet );
		client.packet.clear();
	}
}