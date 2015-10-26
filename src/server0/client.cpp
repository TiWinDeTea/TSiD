#include "../../include/server0/Client.hpp"

bool Client::getNewClient(sf::TcpListener* listener){

    sf::SocketSelector selector;
    selector.add(*listener);

    //std::cout << "* Listening for new clients" << std::endl;

    if( !selector.wait(sf::seconds(60)) ){
        return false;
    }

    if( listener->accept( socket ) != sf::Socket::Done ){
        return false;
    }

    std::cout << "* Client found" << std::endl;

    packet.clear();

    return (this->connectUser());
}

bool Client::connectUser() {

    std::string client_pass, client_real_pass;
    socket.receive(packet);
    packet >> user_name >> client_pass;
    packet.clear();

    std::ifstream user_file( ("UsersData/" + user_name).c_str(), std::ios::in );

    if( user_file.fail() ){

        packet << BadID;
        socket.send( packet );
        packet.clear();
        return false;
    }//else
    
    std::getline( user_file, client_real_pass );

    if( client_real_pass == client_pass ){

        packet << GoodID;
        socket.send( packet );
        packet.clear();
        state = true;
        std::cout << user_name << " - connected" << std::endl;
        return true;
    }//else

    packet << BadID;
    socket.send( packet );
    packet.clear();
    return false;
}

std::string Client::name() const{

    return user_name;
}

void Client::disconnect(){

    socket.disconnect();
    state = false;
}

bool Client::isConnected(){
    return state;
}