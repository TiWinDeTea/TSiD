#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include <cstring>

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


bool fileExist( std::string filename ){

	std::ifstream file (filename.c_str(), std::ios::in);
	return ( !file.fail() );
}


bool listFiles( sf::TcpSocket& client, sf::Packet& cpacket ){
	return false;
}


bool retrieveData( sf::TcpSocket& client, sf::Packet& cpacket ){

	std::string filename;
	unsigned int filesize;
	unsigned int bytes_per_packet;

	if( !(cpacket >> filename >> filesize >> bytes_per_packet) ){
		std::cout << "There was an error reading file infos." << std::endl;
		cpacket.clear();
		cpacket << UnknownIssue;
		client.send(cpacket);
		return false;
	}

	cpacket.clear();

	if( fileExist( filename ) ){
		std::cout << "The file the client tried to send already exists ! Aborting." << std::endl;
		cpacket << AlreadyExist;
		client.send(cpacket);
		return false;
	}

	std::ofstream output_file ( filename.c_str(), std::ios::binary | std::ios::out );

	if( output_file.fail() ){
		std::cout << "Couldn't create file " << filename << "." << std::endl;
		cpacket << ServerFailure;
		client.send(cpacket);
		return false;
	}

	unsigned int loop_number(filesize/bytes_per_packet);
	char* input_data_array = new char[bytes_per_packet];
	sf::Int8 input_data;
	unsigned char percentage_count(0);

	cpacket << ServerReady;
	client.send(cpacket);
	cpacket.clear();

	std::cout << "Download is starting (filename : " << filename << ")" << std::endl;
	for( unsigned int i(0) ; i<loop_number ; ++i){

		client.receive( cpacket );
		if( cpacket.getDataSize() != bytes_per_packet )
			std::cout << i << " -- Received : " << cpacket.getDataSize() << " out of " << bytes_per_packet << std::endl;

		for( unsigned int j(0) ; j<bytes_per_packet ; ++j ){
			cpacket >> input_data;
			input_data_array[j]=static_cast<char>(input_data);
		}

		output_file.write( input_data_array, bytes_per_packet );
		cpacket.clear();

		cpacket << ServerReady;
		client.send( cpacket );				//Sync with client
		cpacket.clear();

		if( static_cast<unsigned char>(100*i/loop_number) > percentage_count ){
			percentage_count = static_cast<unsigned char>(100*i/loop_number);
			std::cout << "[" << static_cast<short>(percentage_count) << "%] - File being transfered" << std::endl;
		}
	}

	filesize -= loop_number * bytes_per_packet;
	if( filesize > 0 ){

		client.receive( cpacket );
		for( unsigned int j(0) ; j < cpacket.getDataSize() ; ++j){
			cpacket >> input_data;
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


bool sendData(){
	return false;
}


bool getClient( sf::TcpSocket& socket ){

	unsigned short port;

	std::cout << "Port to use : ";
	std:: cin >> port;

	sf::TcpListener listener;

	if( listener.listen( port ) != sf::Socket::Done )
	{
		return false;
	}

	std::cout << "Listening." << std::endl;

	if( listener.accept( socket ) != sf::Socket::Done )
	{
		return false;
	}

	std::cout << "Client accepted" << std::endl;
	return true;
}


int main( int argc, char* argv[]){

	sf::TcpSocket client;
	if( !getClient( client ) ){

		std::cout << "Didn't get any client" << std::endl;
		return 1;

	}

	sf::Packet packet;
	int client_command;
	client.receive( packet );

	packet >> client_command;

	switch( static_cast<char>(client_command) ){

		case Upload :

			if( !retrieveData( client, packet ) ){
				std::cout << "Failed to retrieve client data" << std::endl;
			}
			else{
				std::cout << "Client data retrieved successfully" << std::endl;
			}
			client.disconnect();
			return 0;
			break;

		case Download :

			if( !retrieveData( client, packet ) ){
				std::cout << "Failed to send datas to client" << std::endl;
			}
			else{
				std::cout << "Datas sent to client successfully" << std::endl;
			}
			client.disconnect();
			return 0;
			break;

		case Ls :

			if( !listFiles( client, packet ) ){
				std::cout << "Failed to send ls result to client" << std::endl;
			}
			else{
				std::cout << "Successfully listed files to client" << std::endl;
			}
			return 0;
			break;

		default:
			std::cout << "Client sent an invalid command" << std::endl;
			packet.clear();
			packet << UnknownIssue ;
			client.send( packet );
			return 2;

	}



	return 0;
}
