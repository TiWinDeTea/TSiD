\begin{lstlisting}
bool startUpload(std::ifstream& infile, unsigned int& file_size, sf::TcpSocket& server, std::string const& dir, std::string filename)

	std::string directory(dir);
	formatDir(directory);
	if (isFolder(filename)) {
		std::cout << "You are trying to upload a folder... (maybe you forgot to add * ?)"
			<< std::endl;
		return false;
	}
	file_size = getFileLength( filename );
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
	return interpretServerAns(static_cast<char>(server_state));
\end{lstlisting}
