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


int clientLoop(Client* client){

    int client_command;
    do{
        client_command = 0;
        client->packet.clear();
        client->socket.receive( client->packet );
        client->packet >> client_command;

        switch( static_cast<char>(client_command) ){

            case Upload :

                std::cout << "Client sent an upload request" << std::endl;
                if( !retrieveData( *client ) ){
                    std::cout << "Failed to retrieve client data" << std::endl;
                }
                else{
                    std::cout << "Client data retrieved successfully" << std::endl;
                }
                break;

            case Download :

                std::cout << "Client sent a download request" << std::endl;
                if( !sendData( *client ) ){
                    std::cout << "Failed to send datas to client" << std::endl;
                }
                else{
                    std::cout << "Datas sent to client successfully" << std::endl;
                }
                break;

            case Ls :

                std::cout << "Listing files for client" << std::endl;
                if( !listFiles( *client ) ){
                    std::cout << "Failed to send ls result to client" << std::endl;
                }
                else{
                    std::cout << "Successfully listed files to client" << std::endl;
                }
                break;

            case Disconnect :

                std::cout << "Client disconnected" << std::endl;
                break;

            default:
                std::cout << "Client sent an invalid command" << std::endl;
                client->packet.clear();
                client->packet << UnknownIssue ;
                client->socket.send( client->packet );
                return 2;

        }
    }while( static_cast<char>(client_command) != Disconnect );
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