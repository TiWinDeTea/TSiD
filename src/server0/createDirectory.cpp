#include "../../include/server0/createDirectory.hpp"

bool createDirectory(Client& client){
    DIR* directory = opendir(client.path.c_str());
    
    if(directory == NULL){
        std::cout << "\t-The directory name is free" << std::endl;
        
        #ifdef OS_WINDOWS
            
            if (CreateDirectory(client.path.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()){
                tprint();
                setColors("light blue");
                std::cout << "* directory " << client.path << " created" << std::endl;
                setColors("reset");
                return true;
            }
            
            else{
                std::cout << "\t-";
                setColors("light red");
                std::cout << "Error creating the directory" << std::endl;
                setColors("reset");
                return false;
            }
        
        #else
            
            if(!mkdir(client.path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)){
                tprint();
                setColors("light blue");
                std::cout << "* directory " << client.path << " created" << std::endl;
                setColors("reset");
                return true;
            }
            
            else{
                std::cout << "\t-";
                setColors("light red");
                std::cout << "Error creating the directory" << std::endl;
                setColors("reset");
                return false;
            }
        #endif
    }
    
    else{
        std::cout << "\t-The directory already exist" << std::endl;
        return true;
    }
}