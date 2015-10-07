#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include <cstring>
#define NB_BYTE_PER_PACKET 8192

enum SCommand : signed char {
	NotAuthorized = -127,
	TooBig,
	AlreadyExist,
	ServerFailure,
	UnknownIssue,

	ServerReady = 0,

	Upload = 1,
	Download,
	Ls
};

bool interpretServerAns( signed char sanswer){								//Sends message to console telling the problem // success
	
	std::cout << "Server :";

	switch( sanswer ){

	case NotAuthorized :
		std::cout << "action unauthorized" << std::endl;
		return false;

	case TooBig:
		std::cout << "file too heavy" << std::endl;
		return false;
	
	case AlreadyExist:
		std::cout << "this file already exists" << std::endl;
		return false;

	case ServerFailure:
		std::cout << "an error has occured" << std::endl;
		return false;
	
	case UnknownIssue:
		std::cout << "dafuq has happened ?!?" << std::endl;
		return false;

	case ServerReady:
		std::cout << "ready" << std::endl;
		return true;
	
	default:
		std::cout << "unexpected answer from server" << std::endl;
		return false;
	}
}


unsigned int getFileLength( std::string const& filename ) {						//Retrieving file size in bytes

	std::ifstream file( filename.c_str(), std::ios::binary | std::ios::in );
	if( !file.fail() )
	{
		file.seekg( 0, std::ios::end );
		return file.tellg();
	}
	return 0;
}


bool startUpload( std::ifstream& infile, unsigned int& file_size, sf::TcpSocket& server ) {		//Starts an upload by opening the file and telling the server about its name and size
													//Also retrieves server's answer (upload accepted or denied)
	std::string filename;
	
	std::cout << "File name : ";
	std::cin >> filename;

	file_size = getFileLength( filename ) ;
	infile.open(filename.c_str(), std::ios::binary | std::ios::in);

	if( file_size == 0 || infile.fail() ) {
		std::cout << "There was a problem reading the file" << std::endl;
		return false;
	}

	sf::Packet packet;

	packet << Upload << filename << file_size << NB_BYTE_PER_PACKET;
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


bool sconnect( sf::TcpSocket& socket ) {								//Connect the client to the server

	unsigned short remote_port;
	std::string remote_address;

	std::cout << "Remote address : ";
	std::cin >> remote_address;
	std::cout << "Remote port : ";
	std::cin >> remote_port;
	std::cout << "Connecting to the remote @ " << remote_address << ":" << remote_port << std::endl;

	if( socket.connect( remote_address, remote_port ) != sf::Socket::Done ){
		std::cout << "Connection wasn't successful" << std::endl;
		return false;
	}

	std::cout << "Successfully connected" << std::endl;
	return true;
}


bool sendData( sf::TcpSocket& server ){									// Sends a file to the server

	std::ifstream input_file;
	unsigned int file_size;

	if( !startUpload( input_file, file_size, server) ){
		std::cout << "Could not send the file" << std::endl;			//Preparing to upload
		return false;
	}

	unsigned int loop_number=file_size/NB_BYTE_PER_PACKET;
	char input_data_array[NB_BYTE_PER_PACKET];
	sf::Packet spacket;
	spacket.clear();
	unsigned char percentage_count(0);

	std::cout << "Upload is starting" << std::endl;
	for( unsigned int i(0) ; i<loop_number ; ++i ){					//Reading an sending the file

		input_file.read( input_data_array, NB_BYTE_PER_PACKET);
		for( unsigned int j(0) ; j<NB_BYTE_PER_PACKET ; ++j)
			spacket << static_cast<sf::Int8>(input_data_array[j]);

		if( server.send(spacket) == sf::Socket::Disconnected ){

			std::cout << "Lost connection with server !" << std::endl;
			return false;
		}
		spacket.clear();

		server.receive(spacket);						//Sync with server
		spacket.clear();

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
			spacket << file_tail[j];

		if( server.send(spacket) == sf::Socket::Disconnected ){
			std::cout << "Too bad. You almost done it but you were disconnected by server :(" << std::endl;
			delete file_tail;
			return false;
		}

		delete file_tail;

	}

	std::cout << "Transfer terminated successfully" << std::endl;

	return true;
}


bool retrieveData( sf::TcpSocket& server ) {								//Retrieves a file from the server
	return false;
}

int main(int argc, char* argv[]) {

	sf::TcpSocket socket;
	std::string user_input;

	if( !sconnect( socket ) )
			return 1;

	do{
		std::cout << "Do you wish to upload a file ? [y/n/q] ";
		std::cin >> user_input;

		if( user_input == "" || user_input == "y" || user_input == "Y" ) {

			if( !sendData( socket ) ){
				std::cout << "Failed to upload data to server" << std::endl;
			}

		}

		if( user_input == "q"){
			std::cout << "Closing connection and exiting" << std::endl;
			socket.disconnect();
			return 0;
		}

		std::cout << "Do you wish to download a file ? [y/n/q] ";
		std::cin >> user_input;

		if( user_input == "" || user_input == "y" || user_input == "Y" ) {

			if( !retrieveData( socket ) ){
				std::cout << "Failed to retrieve data from server" << std::endl;
			}

		}

		if( user_input == "q" ){
			std::cout << "Closing Connection and exiting" << std::endl;
			socket.disconnect();
			return 0;
		}

	}while(true);
}
