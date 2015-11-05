#include "../../include/server0/createFile.hpp"

char createFile(std::string path){
	
    if( fileExist( path ) ){
        std::cout << "\t-File: " << path << std::endl;
        std::cout << "\t-";
        setColors("light yellow");
        std::cout << "The file already exist, can't be created" << std::endl;
        setColors("reset");
        return AlreadyExist;
    }

    std::ofstream file ( path.c_str(), std::ios::binary | std::ios::out );

    if( file.fail() ){
        file.close();
        std::cout << "\t-File: " << path << std::endl;
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