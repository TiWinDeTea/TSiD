#ifndef RETRIEVEFILELIST_HPP_INCLUDED
#define RETRIEVEFILELIST_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <SFML/Network.hpp>
#include "../common/SCommand.hpp"
#include "../common/termcolor.hpp"


bool retrieveFileList( sf::TcpSocket& server, std::string current_directory );

#endif
