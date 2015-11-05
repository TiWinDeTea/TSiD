#include "getFileLength.hpp"

unsigned int getFileLength( std::string const& filename ) {						//Retrieving file size in bytes

	std::ifstream file( filename.c_str(), std::ios::binary | std::ios::in );
	if( !file.fail() ){
		file.seekg( 0, std::ios::end );
		return static_cast<unsigned int>( file.tellg() );
	}
	return 0;
}
