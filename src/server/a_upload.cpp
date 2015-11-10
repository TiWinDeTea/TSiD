#include "s_a_upload.hpp"

bool a_sendData(Client& client){									// Sends a file to the client

	//here : authorized or forbidden
	client.packet.clear();
	std::cout << "\t-File: " << client.path << std::endl;

	if( !fileExist( client.path ) ){
		client.packet << VoidFileName << 0 << 0;
		client.socket.send( client.packet );
		tprint();
		std::cout << client.name() << " -> Requested file does not exist" << std::endl;
		return false;
	}
	std::cout << "\t-The file exist" << std::endl;

	unsigned int file_size(getFileLength( client.path ));

	if( file_size == 0 ){
		client.packet << ServerFailure << 0 << 0;
		client.socket.send( client.packet );
		tprint();
		std::cout << client.name() << " -> Could not read file size" << std::endl;
		return false;
	}

	if(file_size < 1024 ){
		std::cout << "\t-File size: " << file_size << " B" << std::endl;
	}
	
	else if(file_size < 1024 * 1024 ){
		std::cout << "\t-File size: " << file_size/1024 << " KiB" << std::endl;
	}
	
	else if(file_size < 1024 * 1024 * 1024 ){
		std::cout << "\t-File size: " << file_size/(1024 * 1024)<< " MiB" << std::endl;
	}
	
	else{
		std::cout << "\t-File size: " << file_size/(1024 * 1024 * 1024)<< " GiB" << std::endl;
	}

	client.packet << ServerReady << file_size << NB_BYTE_PER_PACKET;
	client.socket.send( client.packet );
	tprint();
	std::cout << client.name() << " -> Server ready for upload" << std::endl;
	client.packet.clear();

	int client_state;
	client.socket.receive( client.packet );
	client.packet >> client_state;
	client.packet.clear();

	if( static_cast<char>( client_state ) != ClientReady ){
		tprint();
		std::cout << client.name() << " : Download aborted" << std::endl;
		return false;
	}
	tprint();
	std::cout << client.name() << " : Client ready for download" << std::endl;

	std::ifstream input_file( client.path.c_str(), std::ios::binary | std::ios::in );
	

	unsigned int loop_number=file_size/NB_BYTE_PER_PACKET;
	char input_data_array[NB_BYTE_PER_PACKET];
	unsigned char percentage_count(0);

	tprint();
    setColors("light blue");
	std::cout << "* Start uploading " << client.path << " to " << client.name() << std::endl;
    setColors("reset");
	
	for( unsigned int i(0) ; i<loop_number ; ++i ){					//Reading an sending the file

		input_file.read( input_data_array, NB_BYTE_PER_PACKET);
		
		for( unsigned int j(0) ; j<NB_BYTE_PER_PACKET ; ++j)
			client.packet << static_cast<sf::Int8>(input_data_array[j]);

		if( client.socket.send(client.packet) == sf::Socket::Disconnected ){

			tprint();
			std::cout << client.name() << " - ";
            setColors("light red");
            std::cout << "connection lost" << std::endl;
            setColors("reset");
			return false;
		}
		client.packet.clear();

		if( static_cast<unsigned char>(100*i/loop_number) > percentage_count ){
			tprint();
			std::cout << client.name() << " - ";
			setColors("light blue");
			std::cout << "[" << static_cast<short>(percentage_count) << "%]";
			setColors("reset");
			std::cout << " of upload" << std::endl;
			percentage_count = static_cast<unsigned char>(percentage_count + 25);
		}

	}

	file_size -= loop_number * NB_BYTE_PER_PACKET;
	
	if( file_size > 0){								//There is some more to be transferred

		char* file_tail = new char[file_size];
		input_file.read( file_tail, file_size);
		
		for( unsigned int j(0) ; j< file_size ; ++j)
			client.packet << static_cast<sf::Int8>(file_tail[j]);

		if( client.socket.send(client.packet) == sf::Socket::Disconnected ){
			tprint();
			std::cout << client.name() << " - ";
            setColors("light red");
            std::cout << "connection lost" << std::endl;
            setColors("reset");
			delete[] file_tail;
			return false;
		}

		delete[] file_tail;

	}

	tprint();
	std::cout << client.name() << " - ";
	setColors("light blue");
	std::cout << "[100%]";
	setColors("reset");
	std::cout << " Transfer terminated successfully" << std::endl;
	return true;
}
