#include "s_updateInformationsFiles.hpp"

void updateInformationsFiles(std::string path){

	DIR* directory = opendir(path.c_str());

    if( directory != NULL ){
        
	    struct dirent* redfile = NULL;

        while( (redfile = readdir( directory )) != NULL ){

	        std::string tmp( redfile->d_name );

	        if( isFolder(path + "/" + tmp) ){
	            
	            if (tmp[0] != '.'){

	            	createInformationFile(path + "/" + tmp, "@server");
	            	updateInformationsFiles(path + "/" + tmp);
	            }
	        }
	        else{

	        	createInformationFile(path + "/" + tmp, "@server");
	        }
	    }
    }
}