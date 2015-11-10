#include "s_Client.hpp"

Client::Client(){
    
    user_name="";
    state=false;
}

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

    tprint();
    setColors("light blue");
    std::cout << "* Client found" << std::endl;
    setColors("reset");

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
        tprint();
        std::cout << user_name << " - ";
        setColors("light yellow");
        std::cout << "failed to connect, bad id" << std::endl;
        setColors("reset");
        return false;
    }//else
    
    std::getline( user_file, client_real_pass );

    if( client_real_pass == client_pass ){

        packet << GoodID;
        socket.send( packet );
        packet.clear();
        state = true;
        tprint();
        std::cout << user_name << " - ";
        setColors("light green");
        std::cout << "connected" << std::endl;
        setColors("reset");
        return true;
    }//else

    packet << BadID;
    socket.send( packet );
    packet.clear();
    tprint();
    std::cout << user_name << " - ";
    setColors("light yellow");
    std::cout << "failed to connect, bad password" << std::endl;
    setColors("reset");
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

bool Client::isInPrivate(){
    
    if(!path.compare(0,9,"./Private")){

        return true;
    }
    return false;
}

