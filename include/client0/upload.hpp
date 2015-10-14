#ifndef UPLOAD_HPP_INCLUDED
#define UPLOAD_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include "percentageDisplay.hpp"
#include "../common/SCommand.hpp"
#include "serverAnsInterpret.hpp"

#define NB_BYTE_PER_PACKET 8192


unsigned int getFileLength( std::string const& filename );
bool startUpload( std::ifstream& infile, unsigned int& file_size, sf::TcpSocket& server, std::string filename );
bool sendData( sf::TcpSocket& server );

#endif
