#include "c_download.hpp"

bool startDownload( sf::TcpSocket& server, sf::Packet& spacket, unsigned int& filesize, unsigned int& bytes_per_packet, std::ofstream& output_file, std::string& directory, std::string filename ){

	if( fileExist( formatPath(filename) ) ){
		std::cout << "This file already exists ! Aborting." << std::endl;
		return false;
	}

	int server_state;

	spacket.clear();
	spacket << (directory + filename) << Download;
	directory = filename;
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

	output_file.open( formatPath(filename).c_str(), std::ios::binary | std::ios::out );
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
	unsigned int filesize, bytes_per_packet;
	std::ofstream output_file;
	sf::Packet spacket;

	std::cin.ignore();
	std::getline( std::cin, filename );

	if( filename.back() == '*' ){
		
		filename.pop_back();
		return recursiveDownload( server, current_directory + filename );
	}//else

	if( !startDownload( server, spacket, filesize, bytes_per_packet, output_file, current_directory, filename ) ){

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

	std::cout << "Download is starting" << std::endl;
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

bool recursiveDownload( sf::TcpSocket& server, std::string remote_directory ){
	
	///To be done
	//
	//This piece of code is here only to avoid warnings

	sf::Packet spacket;
	spacket << remote_directory;
	server.send( spacket );
	return true;
}
