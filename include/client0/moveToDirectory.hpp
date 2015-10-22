#ifndef MOVE_TO_DIRECTORY_HPP
#define MOVE_TO_DIRECTORY_HPP

#include "SFML/Network.hpp"
#include "../common/SCommand.hpp"
#include "../client0/serverAnsInterpret.hpp"
#include <iostream>
#include <string>

bool moveToDirectory( sf::TcpSocket& server, std::string& current_directory );

#endif
