#ifndef UPLOAD_HPP_INCLUDED
#define UPLOAD_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include "percentageDisplay.hpp"
#include "serverAnsInterpret.hpp"
#include "formatPath.hpp"
#include "../common/SCommand.hpp"
#include "../common/getFileLength.hpp"
#include "../common/isFolder.hpp"

#if defined(WIN32) || defined(WIN64) || defined(_WIN32) || defined(_WIN64)
#else
#include <sys/types.h>
#endif

#define NB_BYTE_PER_PACKET 8192

bool startUpload( std::ifstream& infile, unsigned int& file_size, sf::TcpSocket& server, std::string const& directory, std::string filename );
bool sendData( sf::TcpSocket& server, std::string const& current_directory );
bool uploadFile( sf::TcpSocket& server, std::ifstream& input_file, unsigned int file_size, std::string const& filename );
bool recursiveUpload( sf::TcpSocket& server, std::string remote_directory, std::string current_directory, std::string folder_name );

#endif
