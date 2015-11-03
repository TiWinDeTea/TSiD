#ifndef DOWNLOAD_HPP_INCLUDED
#define DOWNLOAD_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "percentageDisplay.hpp"
#include "../common/SCommand.hpp"
#include "../common/fileExist.hpp"
#include "serverAnsInterpret.hpp"
#include "formatPath.hpp"

bool startDownload( sf::TcpSocket& server, sf::Packet& spacket, unsigned int& filesize, unsigned int& bytes_per_packet, std::ofstream& output_file, std::string& directory, std::string filename );
bool retrieveData( sf::TcpSocket& server, std::string current_directory );
bool downloadFile( sf::TcpSocket& server, sf::Packet& spacket, unsigned int filesize, unsigned int bytes_per_packet, std::ofstream& output_file, std::string const& filename);
bool recursiveDownload( sf::TcpSocket& server, std::string remote_directory );

#endif
