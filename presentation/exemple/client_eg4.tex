\begin{lstlisting}
bool uploadFile (sf::TcpSocket& server, std::ifstream& input_file, unsigned int file_size, std::string const& filename)

	unsigned int loop_number=file_size/NB_BYTE_PER_PACKET;
	char input_data_array[NB_BYTE_PER_PACKET];
	sf::Packet spacket;
	spacket.clear();

	std::cout << "Upload is starting" << std::endl;
	percentageDisplay(0, filename, file_size, 0);

	for (unsigned int i(0) ; i<loop_number ; ++i) {

		input_file.read(input_data_array, NB_BYTE_PER_PACKET);
		for (unsigned int j(0) ; j<NB_BYTE_PER_PACKET ; ++j)
			spacket << static_cast<sf::Int8>(input_data_array[j]);

		if (server.send(spacket) == sf::Socket::Disconnected) {
			std::cout << "Lost connection with server !" << std::endl;
			return false;
		}

		spacket.clear();


		if (i%10 == 0)
			percentageDisplay( static_cast<unsigned char>(100*i/loop_number), filename, file_size, i*NB_BYTE_PER_PACKET );
	}
\end{lstlisting}
