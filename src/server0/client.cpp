#include "../../include/server0/Client.hpp"

Client::client( unsigned short port ){
	
	sf::TcpListener listener;

	if( listener.listen( port ) != sf::Socket::Done ){
		isConnected = false;
	}

	std::cout << "Listening." << std::endl;

	if( listener.accept( socket ) != sf::Socket::Done ){

		isConnected = false;
	}

	std::cout << "Client accepted" << std::endl;
	isConnected = true;

	packet.clear();
}

Client::std::string name(){

	return name;
}

Client::bool isConnected(){

	return isConnected;
}

Client::void disconnect(){

	socket.disconnect();
}