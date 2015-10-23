#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include "../../include/common/SCommand.hpp"
#include "../../include/server0/upload.hpp"
#include "../../include/server0/download.hpp"
#include "../../include/server0/listFiles.hpp"
#include "../../include/server0/Client.hpp"
#include "../../include/server0/formatDirectoryPath.hpp"
#include "../../include/server0/directoryExist.hpp"


int clientLoop(Client* client){

    int client_command;
    sf::Socket::Status client_status;
    do{
        client_command = 0;
        client->packet.clear();
        client_status = client->socket.receive( client->packet );
        client->packet >> client->path;

        formatDirectoryPath(*client);

        client->packet >> client_command;

        switch( static_cast<char>(client_command) ){

            case Upload :

                std::cout << client->name() << " : upload request" << std::endl;
                if( !retrieveData( *client ) ){
                    std::cout << client->name() << " - file download failed" << std::endl;
                }
                else{
                    std::cout << client->name() << " - file downloaded successfully" << std::endl;
                }
                break;

            case Download :

                std::cout << client->name() << " : download request" << std::endl;
                if( !sendData( *client ) ){
                    std::cout << client->name() << " - file upload failed" << std::endl;
                }
                else{
                    std::cout << client->name() << " - file uploaded successfully" << std::endl;
                }
                break;

            case Ls :

                std::cout << client->name() << " : listing request" << std::endl;
                if( !listFiles( *client ) ){
                    std::cout << client->name() << " - file listing failed" << std::endl;
                }
                else{
                    std::cout << client->name() << " - file listed successfully" << std::endl;
                }
                break;

            case Disconnect :

                std::cout << client->name() << " : disconnection" << std::endl;
                break;

            case Exist :

                std::cout << client->name() << " : existing request" << std::endl;
                directoryExist(*client);
                break;

            default:
                std::cout << client->name() << " : invalid command" << std::endl;
                client->packet.clear();
                client->packet << UnknownIssue ;
                client->socket.send( client->packet );
                std::cout << client->name() << " -> invalid command" << std::endl;

        }
    }while( static_cast<char>(client_command) != Disconnect && client_status != sf::Socket::Status::Disconnected );
    client->disconnect();
    return 0;
}

int main(){

    unsigned short port;

    std::cout << "Port to use : ";
    std:: cin >> port;

    std::vector<sf::Thread*> thread_array;
    std::vector<Client*> client_array;
    while (true){

        client_array.push_back(new Client);
        thread_array.push_back(new sf::Thread(&clientLoop, client_array.back()));
        if(client_array.back()->getNewClient(port)){
            thread_array.back()->launch();
        }
        else{
            delete thread_array.back();
            thread_array.pop_back();
            delete client_array.back();
            client_array.pop_back();
        }
    }
}