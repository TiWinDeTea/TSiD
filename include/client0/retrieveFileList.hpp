#ifndef RETRIEVEFILELIST_HPP_INCLUDED
#define RETRIEVEFILELIST_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <SFML/Network.hpp>
#include "../common/SCommand.hpp"
#include "../common/setColors.hpp"


bool retrieveFileList( sf::TcpSocket& server, std::string current_directory );

#endif
