#include "s_createNewUser.hpp"

char createNewUser( std::string const& user_name, std::string const& password ){

    if(createFile("UsersData/"+user_name) == UnknownIssue)
    	return UnknownIssue;

	std::ofstream user_file( ("UsersData/"+user_name).c_str(), std::ios::out);
	
	if( user_file.fail() ){

		std::cout << "\t-File: " << "UsersData/"+user_name << std::endl;
        std::cout << "\t-";
        setColors("light red");
        std::cout << "Error writting in the file" << std::endl;
        setColors("reset");
        return UnknownIssue;
	}

	user_file << password;
	user_file.close();

	if(createDirectory("Private/"+user_name) == UnknownIssue){

		removeFile("UsersData/"+user_name);
		return UnknownIssue;
	}

	if(createDirectory("FilesData/Private/"+user_name) == UnknownIssue){

		removeFile("UsersData/"+user_name);
		return UnknownIssue;
	}

	return Success;
}