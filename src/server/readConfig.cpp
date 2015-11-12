#include "s_readConfig.hpp"

Config readConfig( unsigned short& port ){

	std::ifstream config( "config.txt", std::ios::in );

	bool bconfig[CONFIG_SIZE];

	for(unsigned int i(0) ; i<CONFIG_SIZE ; i++)
		bconfig[i] = true;

	if( config.fail() ){

		setColors("light yellow");
		std::cout << "~ No config file found." << std::endl;
		std::cout << "~ Assuming this is the first time you are using this program\n" << std::endl;
		setColors("reset");

		std::cout << "~ Generating default folders" << std::endl;
		createArchitecture();
		setColors("light green");
		std::cout << "~ Done\n" << std::endl;
		setColors("reset");

		std::cout << "~ Generating default folders" << std::endl;
		updateInformationsFiles("./Public");
		updateInformationsFiles("./Private");
		setColors("light green");
		std::cout << "~ Done\n" << std::endl;
		setColors("reset");

		std::cout << "~ Setting a new user" << std::endl;
		getNewUser();
		setColors("light green");
		std::cout << "~ Done\n" << std::endl;
		setColors("reset");

		std::cout << "Port : ";
		std::cin >> port;
		std::cout << "\n";

		if(!generateDefaultConfig( port )){

			setColors("light red");
			std::cout << "~ Failed to write the default configuration file" << std::endl;
			setColors("reset");
		}
	}
	else{
		
		std::string word, arg, value;
		std::vector<std::string> line_output;
		
		while( std::getline( config, word, '\n') ){
			
			std::istringstream foo(word);
			std::getline( foo, arg, ':' );
			std::getline( foo, value );
			value.erase(0, 1);
			word = switchConfig( arg, value, bconfig );

			if( word.front() == '_' ){
				word.erase(0,1);
				if( word.front() >= '0' && word.front() <= '9' )
					port = static_cast<unsigned short>(strtol( word.c_str(), 0, 10 ));
				else{
					std::cout << "Port : ";
					std::cin >> port;
					std::ostringstream convert;
					convert << port;
					word = convert.str();
				}
			}

			if( word.front() == '*' )
				word.erase(0,1);

			line_output.push_back(arg + ": " + word );
		}
		config.close();

		if( port == 0 ){

			std::cout << "Port : ";
			std::cin >> port;
			std::cout << "\n";
			std::ostringstream convert;   // stream used for the conversion
			convert << port;
			line_output.push_back("port: " + convert.str());
		}

		std::ofstream config_rewrite( "config.txt", std::ios::out | std::ios::trunc );
		
		if( config_rewrite.fail() ){

			setColors("light red");
			std::cout << "~ Could not edit the config file" << std::endl;
			setColors("reset");
		}
		
		else{
			
			for(unsigned int i(0) ; i<line_output.size() ; ++i){
				
				config_rewrite << line_output[i] << '\n';
			}
		}

	}
	return Config(bconfig);
}

bool generateDefaultConfig( unsigned short port ){

	std::cout << "~ Generating config file" << std::endl;
	createFile("config.txt");
	std::ofstream config( "config.txt", std::ios::out );

	if( config.fail() )
		return false;

	config << "port: " << port << '\n'
		<< "regen architecture: false\n"
		<< "new user at restart: false\n"
		<< "auto generate files infos: false\n"
		<< "allow user creation: true\n"
		<< "allow writing in private folders: true\n"
		<< "allow reading in private folders: true\n";

	setColors("light green");
	std::cout << "~ Done\n" << std::endl;
	setColors("reset");
	return true;
}

void createArchitecture(){

	createDirectory("Public");
	createDirectory("Public/music");
	createDirectory("Public/films");
	createDirectory("Public/pictures");
	createDirectory("Public/documents");
	createDirectory("Private");
	createDirectory("FilesData");
	createDirectory("FilesData/Private");
	createDirectory("FilesData/Public");
	createDirectory("UsersData");
	createDirectory("ToConf");
	createDirectory("IPList");
	createDirectory("Downloading_Threads");
}

void getNewUser(){

	std::cout << "\tUser name : ";
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

		setColors("light red");
		std::cout << "~ Could not open user file.\n~ Aborting user creation" << std::endl;
		setColors("reset");
		return;
	}

	createDirectory("Private/"+user_name);
	createDirectory("FilesData/Private/"+user_name);
	user_file << password;
	user_file.close();
}

std::string switchConfig( std::string const& arg, std::string const& value, bool config[CONFIG_SIZE]){

	if( arg == "regen architecture" ){

		if( value=="true" ){

			std::cout << "~ Generating default folders" << std::endl;
			createArchitecture();
			setColors("light green");
			std::cout << "~ Done\n" << std::endl;
			setColors("reset");
		}
		return "false";

	}//else
	
	if( arg == "new user at restart" ){

		if( value=="true" ){

			std::cout << "~ Setting a new user" << std::endl;
			getNewUser();
			setColors("light green");
			std::cout << "~ Done\n" << std::endl;
			setColors("reset");
		}
		return "false";

	}//else

	if( arg == "auto generate files infos"){

		if( value == "true"){
			
			std::cout << "~ Generating default folders" << std::endl;
			updateInformationsFiles("./Public");
			updateInformationsFiles("./Private");
			setColors("light green");
			std::cout << "~ Done\n" << std::endl;
			setColors("reset");
		}
		return "false";

	}

	//Now starting to switch for post-start configuration settings
	
	if( arg == "port" )
		return '_' + value;
	
	if( value == "true" )		//true is default anyway
		return value;

	if( arg == "allow user creation" ){
		config[0] = false;
		return value;
	}//else

	if( arg == "allow reading in private folders" ){
		config[1] = false;
		return value;
	}//else

	if( arg == "allow writing in private folders" ){
		config[2] = false;
		return value;
	}//else

	return '*'+value;

}
