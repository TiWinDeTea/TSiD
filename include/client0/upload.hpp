#ifndef UPLOAD_HPP_INCLUDED
#define UPLOAD_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include "percentageDisplay.hpp"
#include "serverAnsInterpret.hpp"
#include "../common/SCommand.hpp"
#include "../common/getFileLength.hpp"

#define NB_BYTE_PER_PACKET 8192

bool startUpload( std::ifstream& infile, unsigned int& file_size, sf::TcpSocket& server, std::string directory );
bool sendData( sf::TcpSocket& server, std::string current_directory );

#endif
