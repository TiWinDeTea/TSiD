\begin{lstlisting}
bool sendData(sf::TcpSocket& server, std::string const& current_directory) {

	std::ifstream input_file;
	unsigned int file_size;

	std::cin.ignore();
	std::string filename;
	std::getline(std::cin, filename);

	if (filename.back() == '*') {
		filename.pop_back();
		filename.pop_back();
		return recursiveUpload( server, current_directory, ".", filename );
	}

	if (!startUpload(input_file, file_size, server, current_directory, filename)) {

		std::cout << "Could not send the file" << std::endl;
		return false;
	}
	return uploadFile( server, input_file, file_size, filename );
}
\end{lstlisting}
