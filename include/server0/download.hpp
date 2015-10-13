#ifndef DOWNLOAD_HPP_INCLUDED
#define DOWNLOAD_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include "../common/SCommand.cpp"
#include "../common/fileExist.hpp"

bool retrieveData( sf::TcpSocket& client, sf::Packet& cpacket );

#endif
