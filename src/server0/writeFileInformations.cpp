#include "../../include/server0/WriteFileInformations.hpp"

char WriteFileInformations(Client& client){

    if( fileExist("./FilesData" + client.path.substr(1, std::string::npos)) ){
    	setColors("light red");
        std::cout << "\t-The informations file already exist" << std::endl;
        setColors("reset");
        return AlreadyExist;
    }

    if(isFolder(client.path)){
    	return createDirectory("./FilesData" + client.path.substr(1, std::string::npos));
    }

    std::ofstream file ( ("./FilesData" + client.path.substr(1, std::string::npos)).c_str(), std::ios::binary | std::ios::out );

    if( file.fail() ){
        file.close();
        std::cout << "\t-";
        setColors("light red");
        std::cout << "Error creating the informations file" << std::endl;
        setColors("reset");
        return UnknownIssue;
    }
    file << formatedTime() << std::endl;
    file << client.name() << std::endl;
    file.close();
    std::cout << "\t-";
    setColors("light blue");
    std::cout << "Informations file created" << std::endl;
    setColors("reset");
    return Created;
}