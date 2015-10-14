#ifndef UPLOAD_HPP_INCLUDED
#define UPLOAD_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include "../common/SCommand.hpp"
#include "../common/fileExist.hpp"
#include "../common/getFileLength.hpp"

#define NB_BYTE_PER_PACKET 8192

bool sendData( sf::TcpSocket& client, sf::Packet cpacket);

#endif
