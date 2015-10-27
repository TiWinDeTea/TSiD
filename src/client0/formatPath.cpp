#include "../../include/client0/formatPath.hpp"

std::string formatPath( std::string const& path){

	size_t pos( path.find_last_of('/') );

	if( pos != std::string::npos ){
		return path.substr( pos+1 );
	}
	else return path;
}

void formatDir( std::string& dir_path ){

	size_t working_pos;
	std::string left, right;

	while( (working_pos=dir_path.find( "/.." )) != std::string::npos ){

		if( working_pos > 0 ){

			right = dir_path.substr( 0, working_pos - 1 );
			right.erase( right.find_last_of( '/' ) );
		} else {

			right = "";
		}

		left = dir_path.substr( working_pos + 3 );
		
		dir_path = right + left;

	}

	while( (working_pos=dir_path.find( "/." )) != std::string::npos ){

		if( working_pos > 0){

			right = dir_path.substr( 0, working_pos -1 );
		} else {

			right = "";
		}

		left = dir_path.substr( working_pos + 2 );
		dir_path = right + left;
	}

	if( dir_path == "//" )
		dir_path = "/";
}
