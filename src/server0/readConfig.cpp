#include "../../include/server0/readConfig.hpp"

void readConfig(){

	std::ifstream config( "config.txt", std::ios::in );

	if( config.fail() ){

		std::cout << "No config file found." << std::endl;
		std::cout << "Assuming this is the first time you are using this program\n" << std::endl;
		generateDefaultConfig();
		createArchitecture();
		getNewUser();
	}
	else{
		std::string word, l_arg, l_value;
		std::vector<std::string> line_output;
		while( std::getline( config, word, '\n') ){
			std::istringstream foo(word);
			std::getline( foo, l_arg, ':' );
			std::getline( foo, l_value );
			l_value.erase(0, 1);
			line_output.push_back(l_arg + ": " + switchConfig( l_arg, l_value ));
		}
		config.close();
		std::ofstream config_rewrite( "config.txt", std::ios::out | std::ios::trunc );
		if( config_rewrite.fail() ){

			std::cout << "Could not edit the config file.\n Letting this to you\n" << std::endl;
		}
		else{
			for(unsigned int i(0) ; i<line_output.size() ; ++i){
				config_rewrite << line_output[i] << '\n';
			}
		}
	}
}

void generateDefaultConfig(){

	std::cout << "Generating config file" << std::endl;
	std::ofstream config( "config.txt", std::ios::out );
	config << "regen architecture: false\n";
	config << "new user at restart: false\n";

	std::cout << "Done\n" << std::endl;

}

void createArchitecture(){

	std::cout << "Generating default folders" << std::endl;
	createDirectory("Public");
	createDirectory("Public/music");
	createDirectory("Public/films");
	createDirectory("Public/pictures");
	createDirectory("Public/documents");
	createDirectory("Private");
	createDirectory("FilesData");
	createDirectory("FilesData/Private");
	createDirectory("FilesData/Public");
	createDirectory("FilesData/Public/music");
	createDirectory("FilesData/Public/films");
	createDirectory("FilesData/Public/pictures");
	createDirectory("FilesData/Public/documents");
	createDirectory("UsersData");
	createDirectory("ToConf");
	createDirectory("IPList");
	createDirectory("Downloading_Threads");

	std::cout << "Done\n" << std::endl;
}

void getNewUser(){

	std::cout << "Setting a new user\n\tUser name : ";
	std::string user_name, user_password;
	std::cin >> user_name;
	std::cout << "\tUser password : ";
	std::cin.ignore();
	setStdcinEcho( false );
	std::getline( std::cin, user_password );
	setStdcinEcho( true );
	std::cout << "\n" << std::endl;
	newUser( user_name, user_password );
}

void newUser( std::string const& user_name, std::string const& password ){

	std::ofstream user_file( ("UsersData/"+user_name).c_str(), std::ios::out | std::ios::trunc );
	if( user_file.fail() ){

		std::cout << "Could not open user file.\nAborting user creation" << std::endl;
		return;
	}

	createDirectory("Private/"+user_name);
	createDirectory("FilesData/Private/"+user_name);
	user_file << password;
}

std::string switchConfig( std::string const& l_arg, std::string const& l_value ){

	if( l_arg == "regen architecture" ){

		if( l_value=="true" )
			createArchitecture();
		return "false";

	}//else
	
	if( l_arg == "new user at restart" ){

		if( l_value=="true" )
			getNewUser();
		return "false";

	}


	return "";
}

