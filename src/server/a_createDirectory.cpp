#include "s_a_createDirectory.hpp"

bool a_createDirectory(Client& client) {

    switch(createDirectory(client.path)){

        case AlreadyExist:
            
            client.packet << Exist;
            client.socket.send(client.packet);
            client.packet.clear();
            tprint();
            std::cout << client.name() << " -> directory exist" << std::endl;
            return true;
            break;

        case Created:
            
            createInformationFile(client.path, client.name());
            client.packet << Exist;
            client.socket.send(client.packet);
            client.packet.clear();
            tprint();
            std::cout << client.name() << " -> directory exist" << std::endl;
            return true;
            break;

        case UnknownIssue:
            
            client.packet << UnknownIssue;
            client.socket.send(client.packet);
            client.packet.clear();
            tprint();
            std::cout << client.name() << " -> error creating directory" << std::endl;
            return false;
            break;

        default:
            return false;
            break;
    }
}
