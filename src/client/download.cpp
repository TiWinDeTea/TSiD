#include "c_download.hpp"

bool startDownload( sf::TcpSocket& server, sf::Packet& spacket, unsigned int& filesize, unsigned int& bytes_per_packet, std::ofstream& output_file,
	std::string& directory, std::string filename, size_t subst ){

	if( fileExist( formatPath(filename) ) ){
		std::cout << "This file already exists ! Aborting." << std::endl;
		return false;
	}

	int server_state;

	spacket.clear();
	spacket << (directory + filename) << Download;
	server.send( spacket );
	spacket.clear();

	server.receive( spacket );

	if( !(spacket >> server_state >> filesize >> bytes_per_packet) ){
		std::cout << "There was an error reading file infos." << std::endl;
		spacket.clear();
		spacket << UnknownIssue;
		server.send(spacket);
		return false;
	}

	spacket.clear();

	if( subst != std::string::npos ){
		filename = filename.substr( subst );
		output_file.open( ("." + directory + formatPath(filename)).c_str(), std::ios::binary | std::ios::out );
	} else {
		output_file.open( formatPath(filename).c_str(), std::ios::binary | std::ios::out );
	}

	if( output_file.fail() ){
		std::cout << "Couldn't read file " << filename << "." << std::endl;
		spacket << ClientFailure;
		server.send(spacket);
		return false;
	}

	bool state_ok ( interpretServerAns( static_cast<char>(server_state) ) );

	if( !state_ok )
		remove( formatPath(filename).c_str() );

	return state_ok;
}

bool retrieveData( sf::TcpSocket& server, std::string current_directory ){

	std::string filename(current_directory);
	unsigned int filesize(0), bytes_per_packet;
	std::ofstream output_file;
	sf::Packet spacket;

	std::cin.ignore();
	std::getline( std::cin, filename );

	std::cout << "Download Starting" << std::endl;
	if( filename.back() == '*' ){
		
		filename.pop_back();
		return recursiveDownload( server, current_directory + filename, current_directory.size() - 1 );
	}//else

	if( !startDownload( server, spacket, filesize, bytes_per_packet, output_file, current_directory, filename, std::string::npos ) ){

		std::cout << "Could not download" << std::endl;
		return false;
	}//else

	return downloadFile( server, spacket, filesize, bytes_per_packet, output_file, filename );
}
	

bool downloadFile( sf::TcpSocket& server, sf::Packet& spacket, unsigned int filesize, unsigned int bytes_per_packet, std::ofstream& output_file, std::string const& filename ) {

	unsigned int loop_number(filesize/bytes_per_packet);
	char* input_data_array = new char[bytes_per_packet];
	sf::Int8 input_data;

	spacket << ClientReady;
	server.send(spacket);
	spacket.clear();

	percentageDisplay( 100, filename, filesize, 0);

	for( unsigned int i(0) ; i<loop_number ; ++i){

		server.receive( spacket );

		for( unsigned int j(0) ; j<bytes_per_packet ; ++j ){
			spacket >> input_data;
			input_data_array[j]=static_cast<char>(input_data);
		}

		output_file.write( input_data_array, bytes_per_packet );
		spacket.clear();

		if( i%10 == 0 ){
			percentageDisplay( static_cast<unsigned char>(100*i/loop_number), filename, filesize, i*bytes_per_packet);
		}
	}
	
	filesize -= loop_number * bytes_per_packet;
	if( filesize > 0 ){

		server.receive( spacket );
		for( unsigned int j(0) ; j < spacket.getDataSize() ; ++j){
			spacket >> input_data;
			output_file << static_cast<char>(input_data);
		}
		percentageDisplay( 100, filename, filesize + loop_number * bytes_per_packet, filesize + loop_number * bytes_per_packet );
	} 
	std::cout << std::endl << "Transfer terminated successfully" << std::endl;
	delete input_data_array;
	return true;
}

bool recursiveDownload( sf::TcpSocket& server, std::string remote_directory, size_t const& origin ){

	sf::Packet spacket;
	spacket << remote_directory << Ls;
	server.send( spacket );
	spacket.clear();

	sf::Int32 file;
	unsigned int filename_length;

	server.receive( spacket );
	spacket >> file;
	spacket.clear();

	if( !interpretServerAns(static_cast<char>(file)) ){
		return false;
	}

	std::vector<std::string> directory_array;

	do{
		spacket.clear();
		server.receive( spacket );
		
		directory_array.push_back( std::string("") );
		spacket >> filename_length;
		
		for( unsigned int i(0) ; i < filename_length ; ++i ){

			spacket >> file;
			directory_array.back() += static_cast<char>( file );
		}

	}while( filename_length != 0 );

	spacket >> file;
	spacket.clear();
	if( static_cast<char>(file) != EndOfStream )
		return false;

	createDirectory( "." + remote_directory.substr(origin) );
	bool was_successful(true);

	for( unsigned int i(0) ; i < directory_array.size() ; ++i ){

		if( directory_array[i] != "" ){
			size_t tmp( directory_array[i].find(':') );
			if( tmp == 0 ){
		
				directory_array[i].erase(0,1);
				tmp = directory_array[i].find( ':', 1 );
			}
			directory_array[i].erase( tmp );

			if( directory_array[i].back() == '/' ){
				if( directory_array[i].front() != '.' ){
					was_successful = (recursiveDownload( server, remote_directory + directory_array[i], origin ) && was_successful);
				}
			}
			else {
				unsigned int filesize, bytes_per_packet;
				std::ofstream output_file;
				was_successful = startDownload( server, spacket, filesize, bytes_per_packet, output_file, remote_directory, directory_array[i], origin ) &&
					downloadFile( server, spacket, filesize, bytes_per_packet, output_file, directory_array[i] ) &&
					was_successful;
			}
		}
	}

	return was_successful;
}
