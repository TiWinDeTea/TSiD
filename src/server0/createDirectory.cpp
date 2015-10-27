#include "../../include/server0/createDirectory.hpp"

void createDirectory(Client& client){
	std::cout << "\t-Directory: " << client.path << std::endl;
	DIR* directory = opendir(client.path.c_str());
	if(directory == NULL){
		std::cout << "\t-The directory name is free" << std::endl;
		#ifdef OS_WINDOWS
		    if (CreateDirectory(client.path.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
			{
			    client.packet << Exist;
				client.socket.send( client.packet );
				client.packet.clear();
				tprint();
    			setColors("light blue");
				std::cout << "* directory " << client.path << " created" << std::endl;
    			setColors("reset");
			    tprint();
			    std::cout << client.name() << " -> directory created" << std::endl;
			}
			else
			{
			    client.packet << UnknownIssue;
				client.socket.send( client.packet );
				client.packet.clear();
			    tprint();
			    std::cout << client.name() << " -> error creating directory" << std::endl;
			}
		#else
			if(!mkdir(client.path)){
				client.packet << Exist;
				client.socket.send( client.packet );
				client.packet.clear();
				tprint();
    			setColors("light blue");
				std::cout << "* directory " << client.path << " created" << std::endl;
    			setColors("reset");
			    tprint();
			    std::cout << client.name() << " -> directory created" << std::endl;
			}
			else{
				client.packet << UnknownIssue;
				client.socket.send( client.packet );
				client.packet.clear();
			    tprint();
			    std::cout << client.name() << " -> error creating directory" << std::endl;
			}
		#endif
	}
	else{
		client.packet << AlreadyExist;
		client.socket.send( client.packet );
		client.packet.clear();
    	tprint();
    	std::cout << client.name() << " -> directory already exist" << std::endl;
	}
}
