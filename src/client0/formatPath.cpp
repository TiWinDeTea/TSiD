#include "../../include/client0/formatPath.hpp"

std::string formatPath( const std::string& path){
	
	size_t pos( path.find_last_of('/') );

	if( pos != std::string::npos ){
		return path.substr( pos+1 );
	}
	else return path;
}
