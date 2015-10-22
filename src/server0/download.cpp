#include "../../include/server0/download.hpp"

bool retrieveData(Client& client){

	std::string filename;
	unsigned int filesize;
	unsigned int bytes_per_packet;

	if( !(client.packet >> filename >> filesize >> bytes_per_packet) ){
		std::cout << "There was an error reading file infos." << std::endl;
		client.packet.clear();
		client.packet << UnknownIssue;
		client.socket.send(client.packet);
		return false;
	}

	client.packet.clear();

	if( fileExist( filename ) ){
		std::cout << "This file already exists ! Aborting." << std::endl;
		client.packet << AlreadyExist;
		client.socket.send(client.packet);
		return false;
	}

	std::ofstream output_file ( filename.c_str(), std::ios::binary | std::ios::out );

	if( output_file.fail() ){
		std::cout << "Couldn't create file " << filename << "." << std::endl;
		client.packet << ServerFailure;
		client.socket.send(client.packet);
		return false;
	}

	unsigned int loop_number(filesize/bytes_per_packet);
	char* input_data_array = new char[bytes_per_packet];
	sf::Int8 input_data;
	unsigned char percentage_count(0);

	client.packet << ServerReady;
	client.socket.send(client.packet);
	client.packet.clear();

	std::cout << "Download is starting (filename : " << filename << ")" << std::endl;
	for( unsigned int i(0) ; i<loop_number ; ++i){

		client.socket.receive( client.packet );

		for( unsigned int j(0) ; j<bytes_per_packet ; ++j ){
			client.packet >> input_data;
			input_data_array[j]=static_cast<char>(input_data);
		}

		output_file.write( input_data_array, bytes_per_packet );
		client.packet.clear();

		if( static_cast<unsigned char>(100*i/loop_number) > percentage_count ){
			percentage_count = static_cast<unsigned char>(100*i/loop_number);
			std::cout << "[" << static_cast<short>(percentage_count) << "%] - File being transfered" << std::endl;
		}
	}

	filesize -= loop_number * bytes_per_packet;
	if( filesize > 0 ){

		client.socket.receive( client.packet );
		for( unsigned int j(0) ; j < client.packet.getDataSize() ; ++j){
			client.packet >> input_data;
			if(j%4==3)
				output_file << static_cast<char>(input_data);
			//input_data_array[j] = static_cast<char>(input_data);
		}
		//output_file.write( input_data_array, filesize );
	}

	std::cout << "Transfer terminated successfully" << std::endl;
	delete input_data_array;
	return true;
}
