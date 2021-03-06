#ifndef C_MOVE_TO_DIRECTORY_HPP
#define C_MOVE_TO_DIRECTORY_HPP

#include <SFML/Network.hpp>
#include "SCommand.hpp"
#include "c_serverAnsInterpret.hpp"
#include "c_formatPath.hpp"
#include <iostream>
#include <string>

/**
 * moves the user to a given directory
 * @param  server            socket binded to the server (connected)
 * @param  current_directory current working directory (remote)
 * @return                   true if successful, false otherwise
 */
bool moveToDirectory( sf::TcpSocket& server, std::string& current_directory );

#endif
