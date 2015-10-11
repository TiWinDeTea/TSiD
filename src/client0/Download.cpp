#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include "../common/commonfiles.hpp"

bool startDownload( sf::TcpSocket& server, sf::Packet& spacket, unsigned int& filesize, unsigned int& bytes_per_packet, std::ofstream& output_file ){

	std::string filename;
	std::cout << "File to download : ";
	std::cin >> filename;

	if( fileExist( filename ) ){
		std::cout << "This file already exists ! Aborting." << std::endl;
		return false;
	}

	int server_state;

	spacket.clear();
	spacket << Download << filename;
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

	output_file.open( filename.c_str(), std::ios::binary | std::ios::out );
	if( output_file.fail() ){
		std::cout << "Couldn't read file " << filename << "." << std::endl;
		spacket << ClientFailure;
		server.send(spacket);
		return false;
	}


	return interpretServerAns( static_cast<char>(server_state) );
	
}


bool retrieveData( sf::TcpSocket& server ){

	sf::Packet spacket;
	unsigned int filesize(0);
	unsigned int bytes_per_packet; std::ofstream output_file; if( !startDownload( server, spacket, filesize, bytes_per_packet, output_file ) ){
		std::cout << "Could not download" << std::endl;
		return false;
	}
	
	unsigned int loop_number(filesize/bytes_per_packet);
	char* input_data_array = new char[bytes_per_packet];
	sf::Int8 input_data;

	spacket << ClientReady;
	server.send(spacket);
	spacket.clear();

	std::cout << "Download is starting" << std::endl << "\e[?25l";
	for( unsigned int i(0) ; i<loop_number ; ++i){

		server.receive( spacket );

		for( unsigned int j(0) ; j<bytes_per_packet ; ++j ){
			spacket >> input_data;
			input_data_array[j]=static_cast<char>(input_data);
		}

		output_file.write( input_data_array, bytes_per_packet );
		spacket.clear();

		std::cout << "\r[" << static_cast<short>(100*i/loop_number) << "%] - File being transfered ( " << i << "/" << loop_number+(filesize>0) << " )";
	}
	
	filesize -= loop_number * bytes_per_packet;
	if( filesize > 0 ){

		server.receive( spacket );
		for( unsigned int j(0) ; j < spacket.getDataSize() ; ++j){
			spacket >> input_data;
			if(j%4==3)
				output_file << static_cast<char>(input_data);
		}
		std::cout << "\r[100%] - File being transfered ( " << loop_number+1 << "/" << loop_number+1 << ")";
	} 
	std::cout << std::endl << "Transfer terminated successfully" << std::endl << "\e[?25h";
	delete input_data_array;
	return true;
}
