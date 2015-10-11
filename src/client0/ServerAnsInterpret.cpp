#ifndef common_included
#include "../common/commonfiles.hpp"
#endif

bool interpretServerAns( signed char sanswer){								//Sends message to console telling the problem // success
	
	switch( sanswer ){

	case NotAuthorized :
		std::cout << "Message from server : action prohibited" << std::endl;
		return false;

	case TooBig:
		std::cout << "Message from server : file too heavy" << std::endl;
		return false;
	
	case AlreadyExist:
		std::cout << "Message from server : this file already exists" << std::endl;
		return false;

	case VoidFileName:
		std::cout << "Message from server : void file name" << std::endl;
		return false;

	case FileDoesNotExist:
		std::cout << "Message from server : the file does not exist" << std::endl;
		return false;

	case ServerFailure:
		std::cout << "Message from server : an error has occured" << std::endl;
		return false;
	
	case UnknownIssue:
		std::cout << "Message from server : what happened ?!?" << std::endl;
		return false;

	case ServerReady:
		std::cout << "Server ready" << std::endl;
		return true;
	
	default:
		std::cout << "Unexpected answer from server" << std::endl;
		return false;
	}
}