#ifndef CLIENT_HPP_INCLUDED
#define CLIENT_HPP_INCLUDED

#include <SFML/Network.hpp>

class Client {

public:

	client(){ name=""; isConnected=false };
	client( unsigned short port );
	bool isConnected();
	void disconnect();
	std::string name();

	//dirty little code
	sf::Packet packet;
	sf::TcpSocket socket;

private:

	bool isConnected;
	std::string name;
};

#endif
