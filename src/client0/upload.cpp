#include "../../include/client0/upload.hpp"

bool startUpload( std::ifstream& infile, unsigned int& file_size, sf::TcpSocket& server, std::string directory ) {		//Starts an upload (opening file and telling the server its name and size)
													//Also retrieves server's answer (upload accepted or denied)
	std::cin.ignore();
	std::string filename;
	std::getline( std::cin , filename);

	file_size = getFileLength( filename ) ;
	infile.open( formatPath(filename).c_str(), std::ios::binary | std::ios::in);

	if( file_size == 0 || infile.fail() ) {

		std::cout << "There was a problem reading the file" << std::endl;
		return false;
	}

	sf::Packet packet;

	packet << (directory+formatPath(filename)) << Upload << file_size << NB_BYTE_PER_PACKET;
	server.send(packet);
	packet.clear();

	int server_state;

	server.receive(packet);
	if( packet.getDataSize() > sizeof( int ) || !(packet >> server_state) ){

		std::cout << "There was an error retrieving server state" << std::endl;
		return false;
	}
	return interpretServerAns( static_cast<char>(server_state) );
}


bool sendData( sf::TcpSocket& server, std::string current_directory ){									// Sends a file to the server

	std::ifstream input_file;
	unsigned int file_size;

	if( !startUpload( input_file, file_size, server, current_directory ) ){				//Preparing to upload

		std::cout << "Could not send the file" << std::endl;
		return false;
	}

	unsigned int loop_number=file_size/NB_BYTE_PER_PACKET;
	char input_data_array[NB_BYTE_PER_PACKET];
	sf::Packet spacket;
	spacket.clear();

	std::cout << "Upload is starting" << std::endl;
	percentageDisplay( 0, "", file_size, 0 );

	for( unsigned int i(0) ; i<loop_number ; ++i ){					//Reading an sending the file

		input_file.read( input_data_array, NB_BYTE_PER_PACKET);
		for( unsigned int j(0) ; j<NB_BYTE_PER_PACKET ; ++j)
			spacket << static_cast<sf::Int8>(input_data_array[j]);

		if( server.send(spacket) == sf::Socket::Disconnected ){

			std::cout << "Lost connection with server !" << std::endl;
			return false;
		}

		spacket.clear();


		if( i%10 == 0 ){
			percentageDisplay( static_cast<unsigned char>(100*i/loop_number), "", file_size, i*NB_BYTE_PER_PACKET );
		}
	}

	file_size -= loop_number * NB_BYTE_PER_PACKET;
	if( file_size > 0){								//There is some more to be transferred

		char* file_tail = new char[file_size];
		input_file.read( file_tail, file_size);
		for( unsigned int j(0) ; j< file_size ; ++j)
			spacket << static_cast<sf::Int8>(file_tail[j]);

		if( server.send(spacket) == sf::Socket::Disconnected ){

			std::cout << "Too bad. You almost done it but you were disconnected by server :(" << std::endl;
			delete file_tail;
			return false;
		}

		percentageDisplay( 100, "", file_size + loop_number * NB_BYTE_PER_PACKET, file_size + loop_number * NB_BYTE_PER_PACKET );

		delete file_tail;

	}

	std::cout << std::endl << "Transfer terminated successfully" << std::endl;

	return true;
}
