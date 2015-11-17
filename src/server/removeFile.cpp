#include "s_removeFile.hpp"

char removeFile(std::string path){

    if( !fileExist( path ) ){
        std::cout << "\t-File: " << path << std::endl;
        std::cout << "\t-";
        setColors("light yellow");
        std::cout << "The file doesn't exist, can't be deleted" << std::endl;
        setColors("reset");
        return FileDoesNotExist;
    }

    if( remove(path.c_str()) != 0 ){
        std::cout << "\t-File: " << path << std::endl;
        std::cout << "\t-";
        setColors("light red");
        std::cout << "failed to delete the file" << std::endl;
        setColors("reset");
        return UnknownIssue;
    }
    
    else{
        tprint();
        setColors("light blue");
        std::cout << "* file " << path << " deleted" << std::endl;
        setColors("reset");
        return Success;
    }
}