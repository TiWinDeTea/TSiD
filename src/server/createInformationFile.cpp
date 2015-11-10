#include "s_createInformationFile.hpp"

char createInformationFile(std::string path, std::string user_name){

    std::string info_path = "./FilesData" + path.substr(1, std::string::npos); //add "./FilesData" at the begening

    if( fileExist(info_path) ){
    	setColors("light red");
        std::cout << "\t-The informations file already exist" << std::endl;
        setColors("reset");
        return AlreadyExist;
    }

    if(isFolder(path)){
        createDirectory(info_path);
    }

    info_path = info_path.insert(info_path.find_last_of("/") + 1,"."); //insert '.' before the filename
    createFile(info_path);
    std::ofstream file ( info_path.c_str(), std::ios::binary | std::ios::out );

    if( file.fail() ){
        file.close();
        std::cout << "\t-";
        setColors("light red");
        std::cout << "Error writting in the informations file" << std::endl;
        setColors("reset");
        return UnknownIssue;
    }

    file << formatedTime() << std::endl;
    file << user_name << std::endl;
    file.close();
    return Created;
}
