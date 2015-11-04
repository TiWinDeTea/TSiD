#include "../../include/server0/a_createDirectory.hpp"

void a_createDirectory(Client& client) {

    switch(createDirectory(client.path)){

        case AlreadyExist:
            
            client.packet << Exist;
            client.socket.send(client.packet);
            client.packet.clear();
            tprint();
            std::cout << client.name() << " -> directory exist" << std::endl;
            break;

        case Created:
            
            writeFileInformations(client);
            client.packet << Exist;
            client.socket.send(client.packet);
            client.packet.clear();
            tprint();
            std::cout << client.name() << " -> directory exist" << std::endl;
            break;

        case UnknownIssue:
            
            client.packet << UnknownIssue;
            client.socket.send(client.packet);
            client.packet.clear();
            tprint();
            std::cout << client.name() << " -> error creating directory" << std::endl;
            break;

        default:
            
            break;
    }
}
