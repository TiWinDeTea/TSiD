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
	while( std::getline( converter, message, '$' ) && !converter.eof() ){

		std::cout << message;
		converter >> next;
		switch( next ){

		case '$':
			std::cout << '$';
			break;
		
		case '[':

			std::getline( converter, message, ']' );
			if( message == "white" || message == "blue" || message == "cyan" || message == "red" ||
					message == "magenta" || message == "yellow" || message == "green" )
			{
				setColors( "light "+message );
			}
			else{
				std::cout << "$[" << message << ']';
			}
			break;

		default:
			std::cout << '$' << next;
		}
	}
	std::cout << message << '\n' << std::endl;
	setColors("reset");
}
