#include "s_a_createNewUser.hpp"

bool a_createNewUser(Client& client){

	std::string user_name, password;

	if( !(client.packet >> user_name) ){
        client.packet.clear();
        client.packet << UnknownIssue;
        client.socket.send(client.packet);
        tprint();
        std::cout << client.name() << " -> There was an error reading the username" << std::endl;
        return false;
    }

	if( fileExist( "UsersData/"+user_name ) ){

		client.packet.clear();
        client.packet << AlreadyExist;
        client.socket.send(client.packet);
        tprint();
        std::cout << client.name() << " -> The user already exist (" << user_name << ")" << std::endl;
        return false;
	}
    
    unsigned int i = 0;
    while( i < user_name.size() && std::isalnum(user_name[i]))
    	++i;

    if(i != user_name.size()){
    	client.packet.clear();
        client.packet << BadChar;
        client.socket.send(client.packet);
        tprint();
        std::cout << client.name() << " -> Bad character in the username (" << user_name << ")" << std::endl;
        return false;
    }

    client.packet.clear();
    client.packet << ServerReady;
    client.socket.send(client.packet);
    tprint();
    std::cout << client.name() << " -> username is valid (" << user_name << ")" << std::endl;

    client.packet.clear();
    if(client.socket.receive( client.packet ) == sf::Socket::Disconnected){
        
        tprint();
        std::cout << client.name() << " - ";
        setColors("light red");
        std::cout << "connection lost" << std::endl;
        setColors("reset");
        return false;
    }

    int client_command(0);
    if( !(client.packet >> client_command >> password) ){
        
        client.packet.clear();
        client.packet << UnknownIssue;
        client.socket.send(client.packet);
        tprint();
        std::cout << client.name() << " -> There was an error reading the password" << std::endl;
        return false;
    }

    if(client_command != Invite){

    	tprint();
        std::cout << client.name() << " : ";
        setColors("light yellow");
        std::cout << "invalid command (" << client_command << ")" << std::endl;
        setColors("reset");
        client.packet.clear();
        client.packet << UnknownIssue ;
        client.socket.send( client.packet );
        tprint();
        std::cout << client.name() << " -> invalid command" << std::endl;
    }

    if(createNewUser(user_name, password) != Success){
    	
    	client.packet.clear();
        client.packet << UnknownIssue;
        client.socket.send(client.packet);
        tprint();
        std::cout << client.name() << " -> There was an error creating the new client" << std::endl;
        return false;
    }

    client.packet.clear();
    client.packet << Success;
    client.socket.send(client.packet);
    tprint();
    std::cout << client.name() << " -> New user created" << std::endl;

    return true;
}