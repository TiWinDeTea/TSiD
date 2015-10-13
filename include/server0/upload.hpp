#ifndef UPLOAD_HPP_INCLUDED
#define UPLOAD_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include "../common/SCommand.cpp"
#include "../common/fileExist.hpp"

#define NB_BYTE_PER_PACKET 8192

unsigned int getFileLength( std::string const& filename );
bool sendData( sf::TcpSocket& client, sf::Packet cpacket);

#endif
