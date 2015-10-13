#include "../../include/common/fileExist.hpp"

bool fileExist( std::string filename ){

	std::ifstream file (filename.c_str(), std::ios::in);
	return ( !file.fail() );
}
