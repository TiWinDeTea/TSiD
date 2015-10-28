#include "../../include/server0/createFile.hpp"

bool createFile(Client& client){
	if( fileExist( client.path ) ){
        std::cout << "\t-The file already exist" << std::endl;
        return false;
    }
    std::cout << "\t-The filename is free" << std::endl;

    std::ofstream file ( client.path.c_str(), std::ios::binary | std::ios::out );

    if( file.fail() ){
        file.close();
        std::cout << "\t-";
        setColors("light red");
        std::cout << "Error creating the file" << std::endl;
        setColors("reset");
        return false;
    }
    file.close();
    tprint();
    setColors("light blue");
    std::cout << "* file " << client.path << " created" << std::endl;
    setColors("reset");
    return true;
}