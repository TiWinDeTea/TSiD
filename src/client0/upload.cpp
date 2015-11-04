#include "../../include/client0/upload.hpp"

bool startUpload( std::ifstream& infile, unsigned int& file_size, sf::TcpSocket& server, std::string const& dir, std::string filename ) {		//Starts an upload (opening file and telling the server its name and size)
													//Also retrieves server's answer (upload accepted or denied)
	
	std::string directory(dir);
	formatDir(directory);

	if( isFolder( filename ) ){
		
		std::cout << "You are trying to upload a folder... (maybe you forgot to add * ?)"
			<< std::endl;
		return false;
	}

	file_size = getFileLength( filename ) ;
	infile.open( filename.c_str(), std::ios::binary | std::ios::in);
	
	if( file_size == 0 || infile.fail() ) {

		std::cout << "There was a problem reading the file : " << filename << " (maybe that this file is empty ?)" << std::endl;
		return false;
	}

	sf::Packet packet;

	packet << (directory+'/'+formatPath(filename)) << Upload << file_size << NB_BYTE_PER_PACKET;
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

bool sendData( sf::TcpSocket& server, std::string const& current_directory ){

	std::ifstream input_file;
	unsigned int file_size;

	std::cin.ignore();
	std::string filename;
	std::getline( std::cin, filename );

	if( filename.back() == '*' ){
		filename.pop_back();
		filename.pop_back();
		return recursiveUpload( server, current_directory, ".", filename );
	}//else

	if( !startUpload( input_file, file_size, server, current_directory, filename ) ){				//Preparing to upload

		std::cout << "Could not send the file" << std::endl;
		return false;
	}
	return uploadFile( server, input_file, file_size, filename );
}

bool uploadFile( sf::TcpSocket& server, std::ifstream& input_file, unsigned int file_size, std::string const& filename ) {									// Sends a file to the server

	unsigned int loop_number=file_size/NB_BYTE_PER_PACKET;
	char input_data_array[NB_BYTE_PER_PACKET];
	sf::Packet spacket;
	spacket.clear();

	std::cout << "Upload is starting" << std::endl;
	percentageDisplay( 0, filename, file_size, 0 );

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
			percentageDisplay( static_cast<unsigned char>(100*i/loop_number), filename, file_size, i*NB_BYTE_PER_PACKET );
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

		percentageDisplay( 100, filename, file_size + loop_number * NB_BYTE_PER_PACKET, file_size + loop_number * NB_BYTE_PER_PACKET );

		delete file_tail;

	}

	std::cout << std::endl << "Transfer terminated successfully" << std::endl;

	input_file.close();

	return true;
}

bool recursiveUpload( sf::TcpSocket& server, std::string remote_directory, std::string local_directory, std::string folder_name ){

	DIR* directory = opendir( (local_directory+'/'+folder_name).c_str() );

	struct dirent* pointed_elem = NULL;

	if( directory == NULL ){
		
		std::cout << "Could not open the directory : " << local_directory+'/'+folder_name << std::endl;
		return false;
	}

	sf::Packet spacket;
	spacket.clear();

	std::string tmpstr("");
	if( local_directory.size() > 2 )
		tmpstr = local_directory.substr( 2 );

	spacket << remote_directory + tmpstr + '/' + folder_name << Mkdir;
	server.send( spacket );
	spacket.clear();

	server.receive( spacket );
	int s_ans(0);
	spacket >> s_ans;
//For some reason, the client doesn't retrieve any expected answer. Debugging required
/*
	switch( static_cast<char>(s_ans) ){
	
	case Exist: break;
	case AlreadyExist: break;
	default: return false;
	}
*/
	std::cout << "s_ans : " << s_ans << std::endl;
	bool returned(true);

	while( (pointed_elem = readdir( directory )) != NULL){

		if( pointed_elem->d_name[0] != '.' ){
			if( isFolder( local_directory + '/' + folder_name + '/' + pointed_elem->d_name)){

				returned = recursiveUpload( server, remote_directory, local_directory + '/' + folder_name, pointed_elem->d_name ) && returned;
			}else{

				std::ifstream input_file;
				unsigned int file_size;
				std::string file_name( local_directory + '/' + folder_name + '/' + pointed_elem->d_name );

				if( file_name.substr( 0, 2 ) == "./" )
					file_name.erase( 0, 2 );

				returned = startUpload( input_file, file_size, server, remote_directory + '/' + local_directory + '/' + folder_name, file_name )
					&& uploadFile( server, input_file, file_size, file_name )
					&& returned;
			}
		}

	}

	return returned;
}
