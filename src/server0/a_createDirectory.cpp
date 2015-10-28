#include "../../include/server0/a_createDirectory.hpp"

void a_createDirectory(Client& client){
    
    std::cout << "\t-Directory: " << client.path << std::endl;

    if(createDirectory(client)){
        client.packet << Exist;
        client.socket.send( client.packet );
        client.packet.clear();
        tprint();
        std::cout << client.name() << " -> directory exist" << std::endl;
    }
    
    else{
        client.packet << UnknownIssue;
        client.socket.send( client.packet );
        client.packet.clear();
        tprint();
        std::cout << client.name() << " -> error creating directory" << std::endl;
    }
}