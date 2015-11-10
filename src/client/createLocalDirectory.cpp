#include "c_createLocalDirectory.hpp"

bool createDirectory(std::string path){
    DIR* directory = opendir(path.c_str());

    if(directory == NULL){
        
        #ifdef OS_WINDOWS
            
            if (CreateDirectory(path.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()){
                return true;
            }
            
            else{
                return false;
            }
        
        #else
            
            if(!mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)){
                return true;
            }
            
            else{
                return false;
            }
        #endif
    }//else
    return true;
}