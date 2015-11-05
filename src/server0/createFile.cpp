#include "../../include/server0/createFile.hpp"

char createFile(std::string path){
	
    if( fileExist( path ) ){
        std::cout << "\t-The file already exist" << std::endl;
        return AlreadyExist;
    }
    std::cout << "\t-The filename is free" << std::endl;

    std::ofstream file ( path.c_str(), std::ios::binary | std::ios::out );

    if( file.fail() ){
        file.close();
        std::cout << "\t-";
        setColors("light red");
        std::cout << "Error creating the file" << std::endl;
        setColors("reset");
        return UnknownIssue;
    }
    file.close();
    tprint();
    setColors("light blue");
    std::cout << "* file " << path << " created" << std::endl;
    setColors("reset");
    return Created;
}