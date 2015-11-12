#include "c_invite.hpp"

bool invite( sf::TcpSocket& server ){

	std::string user_name;
	std::cout << "\nName of the account to create : ";
	std::cin >> user_name;

	sf::Packet spacket;
	spacket << "/" << Invite << user_name;
	server.send( spacket );
	spacket.clear();

	sf::Int32 s_ans(0);
	server.receive( spacket );
	if( !(spacket >> s_ans) ){
		std::cout << "There was an error retrieving server answer. Aborting" << std::endl;
		return false;
	}
	if( !interpretServerAns( static_cast<char>(s_ans) ) )
		return false;

	spacket.clear();

	std::string password_attempt_1, password_attempt_2;
	setStdcinEcho( false );
	std::cin.ignore();

	bool keep_looping( true );
	do{

		std::cout << "Password : ";
		std::getline( std::cin, password_attempt_1 );
		std::cout << "\nRepeat password : ";
		std::getline( std::cin, password_attempt_2 );

		if( password_attempt_1 != password_attempt_2 )
			std::cout << "\nPasswords don't match !\n" << std::endl;
		else{
			if( password_attempt_1 == "" )
				std::cout << "\nYour password should not be empty\n" << std::endl;
			else keep_looping = false;
		}
	}while( keep_looping );
	setStdcinEcho( true );
	std::cout << std::endl;

	spacket << Invite << password_attempt_1;
	server.send( spacket );

	if( !(spacket >> s_ans) ){
		std::cout << "There was an error retrieving server answer." << std::endl;
		std::cout << "The user creation might have failed." << std::endl;
		return false;
	}

	return interpretServerAns( static_cast<char>( s_ans ) );
}
