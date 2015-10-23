#include "../../include/server0/download.hpp"

bool retrieveData(Client& client){

	unsigned int filesize;
	unsigned int bytes_per_packet;

	if( !(client.packet >> filesize >> bytes_per_packet) ){
		client.packet.clear();
		client.packet << UnknownIssue;
		client.socket.send(client.packet);
		std::cout << client.name() << " -> There was an error reading file infos" << std::endl;
		return false;
	}
	std::cout << "\t-File informations are ok" << std::endl;
	std::cout << "\t-File: " << client.path << std::endl;

	client.packet.clear();

	if( fileExist( client.path ) ){
		client.packet << AlreadyExist;
		client.socket.send(client.packet);
		std::cout << client.name() << " -> File already exists" << std::endl;
		return false;
	}
	std::cout << "\t-The filename is free" << std::endl;

	std::ofstream output_file ( client.path.c_str(), std::ios::binary | std::ios::out );

	if( output_file.fail() ){
		client.packet << ServerFailure;
		client.socket.send(client.packet);
		std::cout << client.name() << " -> Couldn't create file" << std::endl;
		return false;
	}
	std::cout << "\t-File created" << std::endl;

	unsigned int loop_number(filesize/bytes_per_packet);
	char* input_data_array = new char[bytes_per_packet];
	sf::Int8 input_data;
	unsigned char percentage_count(0);

	client.packet << ServerReady;
	client.socket.send(client.packet);
	client.packet.clear();

	std::cout << "* Start downloading " << client.path << " from " << client.name() << std::endl;
	for( unsigned int i(0) ; i<loop_number ; ++i){

		client.socket.receive( client.packet );

		for( unsigned int j(0) ; j<bytes_per_packet ; ++j ){
			client.packet >> input_data;
			input_data_array[j]=static_cast<char>(input_data);
		}

		output_file.write( input_data_array, bytes_per_packet );
		client.packet.clear();

		if( static_cast<unsigned char>(100*i/loop_number) > percentage_count ){
			std::cout << client.name() << " - [" << static_cast<short>(percentage_count) << "%] of download" << std::endl;	//Displaying upload percentage
			percentage_count += 25;
		}
	}

	filesize -= loop_number * bytes_per_packet;
	if( filesize > 0 ){

		if(client.socket.receive( client.packet ) == sf::Socket::Disconnected){
			std::cout << client.name() << " - connection lost" << std::endl;
			return false;
		}
		for( unsigned int j(0) ; j < client.packet.getDataSize() ; ++j){
			client.packet >> input_data;
			if(j%4==3)
				output_file << static_cast<char>(input_data);
			//input_data_array[j] = static_cast<char>(input_data);
		}
		//output_file.write( input_data_array, filesize );
	}

	std::cout << client.name() << " - [100%] Transfer terminated successfully" << std::endl;
	delete input_data_array;
	return true;
}
