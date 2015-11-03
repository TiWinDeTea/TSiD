#include "../../include/server0/createDirectory.hpp"

char createDirectory(std::string path){
    DIR* directory = opendir(path.c_str());
    
    if(directory == NULL){
        std::cout << "\t-The directory name is free" << std::endl;
        
        #ifdef OS_WINDOWS
            
            if (CreateDirectory(path.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()){
                tprint();
                setColors("light blue");
                std::cout << "* directory " << path << " created" << std::endl;
                setColors("reset");
                return Created;
            }
            
            else{
                std::cout << "\t-";
                setColors("light red");
                std::cout << "Error creating the directory" << std::endl;
                setColors("reset");
                return UnknownIssue;
            }
        
        #else
            
            if(!mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)){
                tprint();
                setColors("light blue");
                std::cout << "* directory " << path << " created" << std::endl;
                setColors("reset");
                return Created;
            }
            
            else{
                std::cout << "\t-";
                setColors("light red");
                std::cout << "Error creating the directory" << std::endl;
                setColors("reset");
                return UnknownIssue;
            }
        #endif
    }
    
    else{
        std::cout << "\t-The directory already exist" << std::endl;
        return AlreadyExist;
    }
}