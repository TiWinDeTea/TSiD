#ifndef C_CREATE_DIRECTORY_HPP_INCLUDED
#define C_CREATE_DIRECTORY_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include "c_serverAnsInterpret.hpp"
#include "SCommand.hpp"

/**
 * Tries to create a directory on the remote
 *
 * @param server            socket binded to the server
 * @param current_directory working directory (remote)
 * @return                  true if the folder was succesfully created, false otherwise
 */
bool createDirectory( sf::TcpSocket& server, std::string const& current_directory );

#endif
