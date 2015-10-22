#include "../../include/client0/retrieveFileList.hpp"

bool retrieveFileList( sf::TcpSocket& server, std::string current_directory ){

	sf::Packet spacket;
	
	spacket << current_directory << Ls;
	server.send( spacket );
	spacket.clear();

	sf::Int32 file;
	unsigned int filename_length;

	server.receive( spacket );
	spacket >> file;
	spacket.clear();

	if( static_cast<char>(file) == ServerFailure ){
		std::cout << "ServerFailure" << std::endl;
		return false;
	}


	std::vector<std::wstring> directory_array;

	do{
		server.receive( spacket );
		
		directory_array.push_back( std::wstring(L"") );
		spacket >> filename_length;

		for( unsigned int i(0) ; i < filename_length ; ++i ){

			spacket >> file;
			directory_array.back() += static_cast<wchar_t>( file );
		}
		spacket.clear();

	}while( filename_length != 0 );

	std::sort( directory_array.begin(), directory_array.end() );
	std::cout << std::endl;

	for( unsigned int i(3) ; i < directory_array.size() ; ++i )
		std::wcout << directory_array[i] << std::endl;

	std::cout << std::endl;

	return true;
}
