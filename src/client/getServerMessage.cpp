#include "c_getServerMessage.hpp"

void getServerMessage( sf::TcpSocket& server ){

	sf::Packet spacket;
	std::string message;
	server.receive( spacket );
	if( !(spacket >> message) ){
		std::cout << "Could not retrieve server's message of the day" << std::endl;
		return;
	}

	std::cout << '\n';
	std::istringstream converter( message );

	char next;
	while( std::getline( converter, message, '$' ) ){

		std::cout << message;
		converter >> next;
		if( next == '$' )
			std::cout << '$';
		else{
			std::getline( converter, message, ']' );
			message.erase( 0, 7 );
			message.pop_back();
			setColors( "light "+message );
		}
	}
	std::cout << "\n\n";
}
