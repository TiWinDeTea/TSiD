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
#include "../../include/server0/tprint.hpp"


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

                tprint();
                std::cout << client->name() << " : upload request" << std::endl;
                if( !retrieveData( *client ) ){
                    tprint();
                    std::cout << client->name() << " - ";
                    setColors("light red");
                    std::cout << "file download failed" << std::endl;
                    setColors("reset");
                }
                else{
                    tprint();
                    std::cout << client->name() << " - ";
                    setColors("light green");
                    std::cout << "file downloaded successfully" << std::endl;
                    setColors("reset");
                }
                break;

            case Download :

                tprint();
                std::cout << client->name() << " : download request" << std::endl;
                if( !sendData( *client ) ){
                    tprint();
                    std::cout << client->name() << " - ";
                    setColors("light red");
                    std::cout << "file upload failed" << std::endl;
                    setColors("reset");
                }
                else{
                    tprint();
                    std::cout << client->name() << " - ";
                    setColors("light green");
                    std::cout << "file uploaded successfully" << std::endl;
                    setColors("reset");
                }
                break;

            case Ls :

                tprint();
                std::cout << client->name() << " : listing request" << std::endl;
                if( !listFiles( *client ) ){
                    tprint();
                    std::cout << client->name() << " - ";
                    setColors("light red");
                    std::cout << "file listing failed" << std::endl;
                    setColors("reset");
                }
                else{
                    tprint();
                    std::cout << client->name() << " - ";
                    setColors("light green");
                    std::cout << "file listed successfully" << std::endl;
                    setColors("reset");
                }
                break;

            case Disconnect :

                tprint();
                std::cout << client->name() << " : disconnection" << std::endl;
                client_status = sf::Socket::Disconnected;
                break;

            case Exist :

                tprint();
                std::cout << client->name() << " : existing request" << std::endl;
                directoryExist(*client);
                break;

            case Mkdir :

                tprint();
                std::cout << client->name() << " : directory creation request" << std::endl;
                createDirectory(*client);
                break;

            default:
                tprint();
                std::cout << client->name() << " : invalid command" << std::endl;
                client->packet.clear();
                client->packet << UnknownIssue ;
                client->socket.send( client->packet );
                tprint();
                std::cout << client->name() << " -> invalid command" << std::endl;

        }
    }while(client_status != sf::Socket::Status::Disconnected );
    client->disconnect();
    tprint();
    std::cout << client->name() << " - ";
    setColors("light green");
    std::cout << "disconnected" << std::endl;
    setColors("reset");
}

int main(){

    unsigned short port;

    std::cout << "Port to use : ";
    std:: cin >> port;

    std::vector<sf::Thread*> thread_array;
    std::vector<Client*> client_array;
    sf::TcpListener *listener = new sf::TcpListener;
    if( listener->listen( port ) != sf::Socket::Done ){
        tprint();
        setColors("light blue");
        std::cout << "* failed to listen" << std::endl;
        setColors("reset");
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
                tprint();
                setColors("light blue");
                std::cout << "* memory used by " << client_array[i]->name() << " freed" << std::endl;
                setColors("reset");
                thread_array.erase(thread_array.begin() + i);
                client_array.erase(client_array.begin() + i);
            }
         }

    }
}