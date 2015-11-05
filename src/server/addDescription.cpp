#include "s_addDescription.hpp"

char addDescription(Client& client, std::string description){

	if( !fileExist("./FilesData" + client.path.substr(1, std::string::npos)) ){
    	
    	setColors("light red");
        std::cout << "\t-The informations file doesn't exist" << std::endl;
        setColors("reset");
        return FileDoesNotExist;
    }

    std::ifstream file ( ("./FilesData" + client.path.substr(1, std::string::npos)).c_str(), std::ios::binary | std::ios::in );

    if( file.fail() ){
        
        file.close();
        std::cout << "\t-";
        setColors("light red");
        std::cout << "Error reading the informations file" << std::endl;
        setColors("reset");
        return UnknownIssue;
    }

    std::string file_time;
    if(!std::getline(file,file_time)){
    	
    	file.close();
        std::cout << "\t-";
        setColors("light red");
        std::cout << "Error reading the date of the upload" << std::endl;
        setColors("reset");
        return UnknownIssue;
    }

    std::string file_username;
    if(!std::getline(file,file_username)){
    	
    	file.close();
        std::cout << "\t-";
        setColors("light red");
        std::cout << "Error reading the username of the uploader" << std::endl;
        setColors("reset");
        return UnknownIssue;
    }

    std::string file_description;
    if(!std::getline(file,file_description)){ //if there is already a desciption

    	if(client.name() != file_username){

    		file.close();
	        tprint();
			std::cout << client.name() << " : not authorized to change description" << std::endl;
	        return NotAuthorized;
    	}

    }

    //else: no description or description but user is the file creator
    
    file.close();
    std::ofstream file2 ( ("./FilesData" + client.path.substr(1, std::string::npos)).c_str(), std::ios::binary | std::ios::out | std::ios::trunc);

    if( file2.fail() ){
        
        file2.close();
        std::cout << "\t-";
        setColors("light red");
        std::cout << "Error reading the informations file" << std::endl;
        setColors("reset");
        return UnknownIssue;
    }

    file2 << file_time << std::endl;
    file2 << file_username << std::endl;
    file2 << description << std::endl;
    file2.close();
    return Succes;
}