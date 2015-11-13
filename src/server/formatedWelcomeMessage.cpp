#include "s_formatedWelcomeMessage.hpp"

void formatedWelcomeMessage(std::string& message, Client& client){

	std::ifstream file ( "WelcomeMessage.txt", std::ios::binary | std::ios::in );
	std::string stemp, keyword;
	char ctemp;

    if( file.fail() ){
        file.close();
        std::cout << "\t- ";
        setColors("light red");
        std::cout << "error reading WelcomeMessage.txt" << std::endl;
        setColors("reset");
        return;
    }

    std::getline(file,stemp,'$');
    message = stemp;
    stemp.erase();

    while(std::getline(file,stemp,'$')){

    	std::istringstream iss (stemp);
    	iss >> ctemp;
    	unsigned int i(0);
    	switch(ctemp){

    		case '$':

    			message += "$$";
    			i += 2;
    			break;

    		case '[':
    			i += 3;
    			std::getline(iss,keyword,']');

    			if(keyword == "user"){
    				message += client.name();
    				i += 4;
    			}
    			else if(keyword == "day"){
    				message += formatedTime().substr(0,3);
    				i += 3;
    			}
    			else if(keyword == "date"){
    				message += formatedTime().substr(4,8);
    				i += 4;
    			}
    			else if(keyword == "hour"){
    				message += formatedTime().substr(13,5);
    				i += 4;
    			}
    			else{
    				message += ("$[" + keyword + "]");
    				i += (keyword.size());
    			}
    			break;

    		default:

    			message += "$";
    			++i;
    			break;
    	}
    	i--;
    	stemp.erase(0,i);
    	message += stemp;
    	stemp.erase();
    	ctemp = 0;
    }
    file.close();
}