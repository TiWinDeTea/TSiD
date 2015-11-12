#include "c_help.hpp"

void help(){

	std::string user_input;
	std::cin.ignore();
	std::getline( std::cin, user_input );
	
	if( user_input == "!" ){

		std::cout << "Sends a command to local shell." << std::endl
			<< "Usage : !<command>\n" << std::endl;
	}
	else if( user_input == "help" ){

		std::cout << "Prints a list of available commands" << std::endl;
	}
	else if( user_input == "ls" ){

		std::cout << "Prints the list of files and folders in the current remote directory" << std::endl;
	}
	else if( user_input == "put" ){

		std::cout << "Uploads a local file or a folder to the server" <<std::endl
			<< "Usage : put <file> OR put <folder>/*" << std::endl;
	}
	else if( user_input == "get" ){
		
		std::cout << "Downloads a file or a folder from the server" << std::endl
			<< "Usage : get <file> OR get <folder>/*" << std::endl;
	}
	else if( user_input == "bye" || user_input == "quit" || user_input == "exit" ){

		std::cout << "Disconnects you from the server gracefully" << std::endl;
	}
	else if( user_input == "cd" ){

		std::cout << "Change the remote working directory" << std::endl
			<< "Usage : cd <folder>" << std::endl;
	}
	else if( user_input == "mkdir" ){

		std::cout << "Creates a directory in the remote working directory" << std::endl
			<< "Usage : mkdir <directory>" << std::endl;
	}
	else if( user_input == "passwd" ){

		std::cout << "Changes the user password" << std::endl
			<< "Usage : passwd" << std::endl;
	}
	else if( user_input == "msg" ){

		std::cout << "Sends a message to the server's console" << std::endl
			<< "Usage : msg <message>" << std::endl;
	}
	else if( user_input == "version" ){

		std::cout << "Outputs version information" << std::endl;
	}
	else{
		std::cout << "No advanced help entry for this command" << std::endl;
	}
}
