#ifndef DOWNLOAD_HPP_INCLUDED
#define DOWNLOAD_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include "include/common/SCommand.hpp"
#include "include/common/fileExist.hpp"

bool retrieveData( sf::TcpSocket& client, sf::Packet& cpacket );

#endif
