#include "../../include/client0/userInputInterpret.hpp"

void userInputInterpret( sf::TcpSocket& server, std::string user_id ){

	std::string user_input;
	std::string current_directory("/");

	do{
		std::cout << user_id << "@TSiD " << current_directory << " $ ";
		std::cin >> user_input;

		if( user_input == "help"){

			std::cout << "available commands :	help" << std::endl
				<< "			ls" << std::endl
				<< "			put" << std::endl
				<< "			get" << std::endl
				<< "			bye / quit / exit" << std::endl
				<< "			cd" << std::endl
				<< "			!" << std::endl
				<< std::endl;
		}
		else if( user_input == "put" ){

			if( !sendData( server, current_directory ) )
				std::cout << "Failed to upload data to server" << std::endl;
		}
		else if( user_input == "get" ){

			if( !retrieveData( server, current_directory ) )
				std::cout << "Failed to retrieve data from server" << std::endl;
		}
		else if( user_input == "ls" ){

			if( !retrieveFileList( server, current_directory ) )
				std::cout << "Failed to retrieve file list" << std::endl;
		}
		else if( user_input == "cd" ){

			if( !moveToDirectory( server, current_directory ) )
				std::cout << "Failed to move" << std::endl;
		}
		else if( user_input[0] == '!' ){

			std::string tmp;
			std::getline( std::cin, tmp );
			user_input.erase(0,1);
			user_input+=tmp;
			std::cout << std::endl;
			system( user_input.c_str() );
			std::cout << std::endl;
		}
		else if( user_input == "mkdir" ){

			if( !createDirectory( server, current_directory ) )
				std::cout << "Failed to create the directory" << std::endl;
		}
		else if( user_input != "bye" && user_input != "exit" && user_input != "quit" ){

			std::cout << "TSiD : " << user_input << " : command not found."
			       << std::endl << " Type 'help' for a list of available commands" << std::endl << std::endl;
		}

	}while( user_input != "bye" && user_input != "exit" && user_input != "quit" );

	return;
}
