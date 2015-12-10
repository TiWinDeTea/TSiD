\begin{lstlisting}
bool uploadFile (sf::TcpSocket& server, std::ifstream& input_file, unsigned int file_size, std::string const& filename)

	file_size -= loop_number * NB_BYTE_PER_PACKET;
	if (file_size > 0) {
		char* file_tail = new char[file_size];
		input_file.read( file_tail, file_size);
		for (unsigned int j(0) ; j< file_size ; ++j)
			spacket << static_cast<sf::Int8>(file_tail[j]);

		if (server.send(spacket) == sf::Socket::Disconnected) {

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
\end{lstlisting}
