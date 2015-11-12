#include "s_server.hpp"

void clientLoop(Client* client, Config* config){

    sf::Socket::Status client_status;
    do{
        int client_command(0);
        client->packet.clear();
        client_status = client->socket.receive( client->packet );
        client->packet >> client->path;
        client->packet >> client_command;

        if(!formatDirectoryPath(*client, config)){
            client_command = InvalidPath;
        }

        switch( static_cast<char>(client_command) ){

            case Upload :

                tprint();
                std::cout << client->name() << " : ";
                setColors("light magenta");
                std::cout << "upload request" << std::endl;
                setColors("reset");

                if(client->isInPrivate() && !config->privateFolderWritingAllowed()){
                    
                    tprint();
                    std::cout << client->name() << " - ";
                    setColors("light yellow");
                    std::cout << "/Private folder writting not allowed" << std::endl;
                    setColors("reset");
                    client->packet.clear();
                    client->packet << NotAuthorized;
                    client->socket.send( client->packet );
                    tprint();
                    std::cout << client->name() << " -> Not authorized" << std::endl;
                }
                else{

                    if( !a_retrieveData( *client ) ){
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
                }
                break;

            case Download :

                tprint();
                std::cout << client->name() << " : ";
                setColors("light magenta");
                std::cout << "download request" << std::endl;
                setColors("reset");

                if(client->isInPrivate() && !config->privateFolderReadingAllowed()){
                    
                    tprint();
                    std::cout << client->name() << " - ";
                    setColors("light yellow");
                    std::cout << "/Private folder reading not allowed" << std::endl;
                    setColors("reset");
                    client->packet.clear();
                    client->packet << NotAuthorized;
                    client->socket.send( client->packet );
                    tprint();
                    std::cout << client->name() << " -> Not authorized" << std::endl;
                }
                else{

                    if( !a_sendData( *client ) ){
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
                }
                break;

            case Ls :

                tprint();
                std::cout << client->name() << " : ";
                setColors("light magenta");
                std::cout << "listing request" << std::endl;
                setColors("reset");

                if( !a_listFiles( *client, config ) ){
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

            case Exist :

                tprint();
                std::cout << client->name() << " : ";
                setColors("light magenta");
                std::cout << "existing request" << std::endl;
                setColors("reset");
                a_directoryExist(*client);
                tprint();
                std::cout << client->name() << " - ";
                setColors("light green");
                std::cout << "exist request successfully answered" << std::endl;
                setColors("reset");
                break;

            case Mkdir :

                tprint();
                std::cout << client->name() << " : ";
                setColors("light magenta");
                std::cout << "directory creation request" << std::endl;
                setColors("reset");

                if(client->isInPrivate() && !config->privateFolderWritingAllowed()){
                    
                    tprint();
                    std::cout << client->name() << " - ";
                    setColors("light yellow");
                    std::cout << "/Private folder writting not allowed" << std::endl;
                    setColors("reset");
                    client->packet.clear();
                    client->packet << NotAuthorized;
                    client->socket.send( client->packet );
                    tprint();
                    std::cout << client->name() << " -> Not authorized" << std::endl;
                }
                else{
                    
                    if( !a_createDirectory(*client) ){
                        tprint();
                        std::cout << client->name() << " - ";
                        setColors("light red");
                        std::cout << "file creation failed" << std::endl;
                        setColors("reset");
                    }

                    else{
                        tprint();
                        std::cout << client->name() << " - ";
                        setColors("light green");
                        std::cout << "directory creation request successfully answered" << std::endl;
                        setColors("reset");
                    }
                }
                break;

            case Disconnect :

                tprint();
                std::cout << client->name() << " : ";
                setColors("light magenta");
                std::cout << "disconnection" << std::endl;
                setColors("reset");
                client_status = sf::Socket::Disconnected;
                break;

            case InvalidPath:

                tprint();
                std::cout << client->name() << " : ";
                setColors("light yellow");
                std::cout << "invalid path" << std::endl;
                setColors("reset");
                client->packet.clear();
                client->packet << InvalidPath;
                client->socket.send( client->packet );
                tprint();
                std::cout << client->name() << " -> invalid path" << std::endl;

            default:
                
                tprint();
                std::cout << client->name() << " : ";
                setColors("light yellow");
                std::cout << "invalid command (" << client_command << ")" << std::endl;
                setColors("reset");
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
    setColors("light yellow");
    std::cout << "disconnected" << std::endl;
    setColors("reset");
}

int main(){

    setColors("reset");
    unsigned short port(0);
    Config config(readConfig( port ));

    std::vector<sf::Thread*> thread_array;
    std::vector<Client*> client_array;
    sf::TcpListener *listener = new sf::TcpListener;
    
    if( listener->listen( port ) != sf::Socket::Done ){
        tprint();
        setColors("light red");
        std::cout << "* failed to listen" << std::endl;
        setColors("reset");
        std::cout << "press enter to quit";
        std::string wait_for_input;
        std::cin.ignore();
        std::getline( std::cin, wait_for_input );
        return EXIT_FAILURE;
    }
    
    while (true){

        client_array.push_back(new Client);
        thread_array.push_back(new sf::Thread(std::bind(&clientLoop, client_array.back(), &config)));
        
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
                --i;
            }
         }

    }
    return EXIT_SUCCESS;
}
