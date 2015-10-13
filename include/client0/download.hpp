#ifndef DOWNLOAD_HPP_INCLUDED
#define DOWNLOAD_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include "percentageDisplay.hpp"
#include "include/common/SCommand.hpp"

bool startDownload( sf::TcpSocket& server, sf::Packet& spacket, unsigned int& filename, unsigned int& bytes_per_packet, std::ofstream& output_file, std::string& filename );
bool retrieveData( sf::TcpSocket& server );

#endif
