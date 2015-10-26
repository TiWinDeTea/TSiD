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
#include "../../include/server0/createDirectory.hpp"
#include "../../include/server0/tcout.hpp"


void clientLoop(Client* client){

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

                tcout() << client->name() << " : upload request" << std::endl;
                if( !retrieveData( *client ) ){
                    tcout() << client->name() << " - file download failed" << std::endl;
                }
                else{
                    tcout() << client->name() << " - file downloaded successfully" << std::endl;
                }
                break;

            case Download :

                tcout() << client->name() << " : download request" << std::endl;
                if( !sendData( *client ) ){
                    tcout() << client->name() << " - file upload failed" << std::endl;
                }
                else{
                    tcout() << client->name() << " - file uploaded successfully" << std::endl;
                }
                break;

            case Ls :

                tcout() << client->name() << " : listing request" << std::endl;
                if( !listFiles( *client ) ){
                    tcout() << client->name() << " - file listing failed" << std::endl;
                }
                else{
                    tcout() << client->name() << " - file listed successfully" << std::endl;
                }
                break;

            case Disconnect :

                tcout() << client->name() << " : disconnection" << std::endl;
                client_status = sf::Socket::Disconnected;
                break;

            case Exist :

                tcout() << client->name() << " : existing request" << std::endl;
                directoryExist(*client);
                break;

            case Mkdir :

                tcout() << client->name() << " : directory creation request" << std::endl;
                createDirectory(*client);
                break;

            default:
                tcout() << client->name() << " : invalid command" << std::endl;
                client->packet.clear();
                client->packet << UnknownIssue ;
                client->socket.send( client->packet );
                tcout() << client->name() << " -> invalid command" << std::endl;

        }
    }while(client_status != sf::Socket::Status::Disconnected );
    client->disconnect();
    tcout() << client->name() << " - disconnected" << std::endl;
}

int main(){

    unsigned short port;

    std::cout << "Port to use : ";
    std:: cin >> port;

    std::vector<sf::Thread*> thread_array;
    std::vector<Client*> client_array;
    sf::TcpListener *listener = new sf::TcpListener;
    if( listener->listen( port ) != sf::Socket::Done ){
        tcout() << "* failed to listen" << std::endl;
        return false;
    }
    while (true){

        client_array.push_back(new Client);
        thread_array.push_back(new sf::Thread(&clientLoop, client_array.back()));
        if(client_array.back()->getNewClient(listener)){
            thread_array.back()->launch();
        }
        else{
            delete thread_array.back();
            thread_array.pop_back();
            delete client_array.back();
            client_array.pop_back();
        }
        for(unsigned int i(0); i < client_array.size(); ++i) {
            if (!client_array[i]->isConnected()){
                tcout() << "* memory used by " << client_array[i]->name() << " freed" << std::endl;
                thread_array.erase(thread_array.begin() + i);
                client_array.erase(client_array.begin() + i);
            }
         }

    }
}