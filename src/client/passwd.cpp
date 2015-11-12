#include "c_passwd.hpp"

void passwd( sf::TcpSocket& server ){

	std::cin.ignore();
	setStdcinEcho( false );
	std::string previous_pass, new_pass_attempt_1, new_pass_attempt_2;
	std::cout << "\nPrevious password: ";
	std::getline( std::cin, previous_pass );
	std::cout << "\nNew password: ";
	std::getline( std::cin, new_pass_attempt_1 );
	std::cout << "\nRepeat password: ";
	std::getline( std::cin, new_pass_attempt_2 );
	setStdcinEcho( true );
	std::cout << '\n';

	if( new_pass_attempt_1 != new_pass_attempt_2 ){
		std::cout << "Passwords don't match." << std::endl;
		return;
	}

	sf::Packet spacket;
	spacket << "/" << Passwd << previous_pass << new_pass_attempt_1;
	server.send( spacket );
	spacket.clear();

	server.receive( spacket );
	int s_ans;
	spacket >> s_ans;

	interpretServerAns( static_cast<char>(s_ans) );
}
