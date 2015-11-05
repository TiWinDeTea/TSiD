#include "../../include/server0/createDirectory.hpp"

char createDirectory(std::string path){
    DIR* directory = opendir(path.c_str());

    if(directory == NULL){
        
        #ifdef OS_WINDOWS
            
            if (CreateDirectory(path.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()){
                tprint();
                setColors("light blue");
                std::cout << "* directory " << path << " created" << std::endl;
                setColors("reset");
                return Created;
            }
            
            else{
                std::cout << "\t-Directory: " << path << std::endl;
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
                std::cout << "\t-Directory: " << path << std::endl;
                std::cout << "\t-";
                setColors("light red");
                std::cout << "Error creating the directory" << std::endl;
                setColors("reset");
                return UnknownIssue;
            }
        #endif
    }
    
    else{
        std::cout << "\t-Directory: " << path << std::endl;
        std::cout << "\t-";
        setColors("light yellow");
        std::cout << "The directory already exist, can't be created" << std::endl;
        setColors("reset");
        return AlreadyExist;
    }
}