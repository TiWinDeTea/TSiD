#ifndef DOWNLOAD_HPP_INCLUDED
#define DOWNLOAD_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include "percentageDisplay.hpp"
#include "../common/SCommand.hpp"
#include "../common/fileExist.hpp"
#include "serverAnsInterpret.hpp"

bool startDownload( sf::TcpSocket& server, sf::Packet& spacket, unsigned int& filesize, unsigned int& bytes_per_packet, std::ofstream& output_file, std::string& filename );
bool retrieveData( sf::TcpSocket& server );

#endif
