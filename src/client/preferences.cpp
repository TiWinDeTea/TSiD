#include "c_preferences.hpp"

bool loadPreferences( std::string& user_name, std::string& ip_address, unsigned short& port ){

	std::ifstream pref_file( "preferences.txt", std::ios::in | std::ios::binary );
	if( pref_file.fail() )
		return false;

	pref_file >> user_name;
	pref_file >> ip_address;
	pref_file >> port;

	std::string user_answer;
	std::cout << "Connect as " << user_name << '@' << ip_address << ':' << port << " ?[Y\\n] ";
	std::getline( std::cin, user_answer );

	return (user_answer.size() == 0 || (user_answer != "N" && user_answer != "n"));
}

bool writePreferences( std::string const& user_name, std::string const& ip_address, unsigned short port ){

	std::ofstream pref_file( "preferences.txt", std::ios::out | std::ios::trunc );
	if( pref_file.fail() )
		return false;

	pref_file << user_name << '\n';
	pref_file << ip_address << '\n';
	pref_file << port << '\n';
	return true;
}
