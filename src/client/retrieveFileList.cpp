#include "c_retrieveFileList.hpp"

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


	std::vector<std::string> directory_array;

	do{
		server.receive( spacket );
		
		directory_array.push_back( std::string("") );
		spacket >> filename_length;

		for( unsigned int i(0) ; i < filename_length ; ++i ){

			spacket >> file;
			directory_array.back() += static_cast<char>( file );
		}
		spacket.clear();

	}while( filename_length != 0 );

	std::sort( directory_array.begin(), directory_array.end() );
	std::cout << std::endl;

	size_t max_file_name_size(0), tmp;
	for( unsigned int i(0) ; i < directory_array.size() ; ++i ){

		tmp = directory_array[i].find('|');
		if( tmp == 0 )
			tmp = directory_array[i].find( '|', 1 );

		if( tmp > max_file_name_size && tmp != std::string::npos )
			max_file_name_size = tmp;
	}

	std::cout << "Name";
	for( unsigned int i(4) ; i < max_file_name_size ; ++i )
		std::cout << ' ';
	std::cout << "  Creat. Date   Creator" << std::endl << std::endl;

	setColors("light blue");

	for( unsigned int i(0) ; i < directory_array.size() ; ++i ){

		formatFilesDisplay( directory_array[i], max_file_name_size );
		if( directory_array[i][0] == '|' && directory_array[i][1] != '.' )
			std::cout << directory_array[i].substr(1) << std::endl;
	}

	setColors("light green"); //for files

	for( unsigned int i(0) ; i < directory_array.size() ; ++i )
		if( directory_array[i][0] != '|' )
			std::cout << directory_array[i] << std::endl;

	std::cout << std::endl;
	setColors("reset");

	return true;
}

void formatFilesDisplay( std::string& file, size_t max_file_size ){

	bool is_folder(false);

	if( file[0] == '|' ){

		file.erase(0,1);
		is_folder = true;
	}

	std::string file_name( file.substr(0, file.find('|')) );		//Considering the string is always well formated and that the console width is wide enough
	file.erase(0, file.find('|')+1);
	std::string file_creation_date( file.substr(0, file.find('|')) );
	std::string file_creator( file.erase(0, file.find('|')+1) );

	for( size_t i(file_name.size()-1) ; i < max_file_size ; ++i ){
		file_name+=' ';
	}
	if(is_folder)
		file_name = '|' + file_name;
	
	file = file_name + " " + file_creation_date + "  " + file_creator;
}
