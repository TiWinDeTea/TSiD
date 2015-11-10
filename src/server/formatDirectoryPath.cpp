#include "s_formatDirectoryPath.hpp"

bool formatDirectoryPath(Client& client, Config* config){

	std::size_t pos = client.path.find("..");
	while(pos != std::string::npos){ //while there is .. not analysed somewhere
		
		if(pos == 0) //path start with '..'
			return false;

		if(client.path[pos - 1] == '/'){ //there is '/..'

			if(pos + 2 == client.path.size()) //path end by '/..'
				return false;

			if(client.path[pos + 2] == '/') //there is a '/' after '/..'
				return false;
		}

		pos = client.path.find("..", pos + 1);
	}


	if (!client.path.compare(0,8,"/Private")){
		
		client.path.insert(8, "/" + client.name());
		
		if(!config->privateFolderReadingAllowed() &&  !config->privateFolderWritingAllowed()){

			return false;
		}
	}
	
	else{
		client.path = "/Public" + client.path;
	}
	client.path = '.' + client.path;

	return true;
}