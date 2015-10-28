#include "../../include/server0/formatDirectoryPath.hpp"

void formatDirectoryPath(Client& client){

	if (!client.path.compare(0,8,"/Private")){
		
		client.path.insert(8, "/" + client.name());
	}
	
	else{
		client.path = "/Public" + client.path;
	}
	client.path = '.' + client.path;
}