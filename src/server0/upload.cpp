#include "../../include/server0/upload.hpp"

bool sendData(Client& client){									// Sends a file to the client

	std::string filename;
	
	if( !(client.packet >> filename) ){
		std::cout << "Could not read packet" << std::endl;
		client.packet.clear();
		client.packet << UnknownIssue << 0 << 0;
		client.socket.send( client.packet );
		return false;
	}
	client.packet.clear();

	//here : authorized or forbidden
	
	if( !fileExist( filename ) ){
		std::cout << "Requested file does not exist" << std::endl;
		client.packet << VoidFileName << 0 << 0;
		client.socket.send( client.packet );
		return false;
	}

	unsigned int file_size(getFileLength( filename ));

	if( file_size == 0 ){
		std::cout << "Could not read file size" << std::endl;
		client.packet << ServerFailure << 0 << 0;
		client.socket.send( client.packet );
		return false;
	}
	
	client.packet << ServerReady << file_size << NB_BYTE_PER_PACKET;
	client.socket.send( client.packet );
	client.packet.clear();

	std::ifstream input_file( filename.c_str(), std::ios::binary | std::ios::in );
	
	int client_state;
	client.socket.receive( client.packet );
	client.packet >> client_state;
	client.packet.clear();

	if( static_cast<char>( client_state ) != ClientReady ){
		std::cout << "Aborted by client" << std::endl;
		return false;
	}


	unsigned int loop_number=file_size/NB_BYTE_PER_PACKET;
	char input_data_array[NB_BYTE_PER_PACKET];
	unsigned char percentage_count(0);

	std::cout << "Uploading " << filename << " to client" << std::endl;
	for( unsigned int i(0) ; i<loop_number ; ++i ){					//Reading an sending the file

		input_file.read( input_data_array, NB_BYTE_PER_PACKET);
		for( unsigned int j(0) ; j<NB_BYTE_PER_PACKET ; ++j)
			client.packet << static_cast<sf::Int8>(input_data_array[j]);

		if( client.socket.send(client.packet) == sf::Socket::Disconnected ){

			std::cout << "Lost connection with client !" << std::endl;
			return false;
		}
		client.packet.clear();

		if( static_cast<unsigned char>(100*i/loop_number) > percentage_count ){
			percentage_count = static_cast<unsigned char>(100*i/loop_number);
			std::cout << "[" << static_cast<short>(percentage_count) << "%] - File being transfered" << std::endl;	//Displaying upload percentage
		}

	}

	file_size -= loop_number * NB_BYTE_PER_PACKET;
	if( file_size > 0){								//There is some more to be transferred

		char* file_tail = new char[file_size];
		input_file.read( file_tail, file_size);
		for( unsigned int j(0) ; j< file_size ; ++j)
			client.packet << file_tail[j];

		if( client.socket.send(client.packet) == sf::Socket::Disconnected ){
			std::cout << "Disconnected" << std::endl;
			delete file_tail;
			return false;
		}

		delete file_tail;

	}

	std::cout << "Transfer terminated successfully" << std::endl;

	return true;
}
