#ifndef RETRIEVEFILELIST_HPP_INCLUDED
#define RETRIEVEFILELIST_HPP_INCLUDED

#include <iostream>
#include <SFML/Network.hpp>
#include "../common/SCommand.hpp"


bool retrieveFileList( sf::TcpSocket& server, std::string current_directory );

#endif
