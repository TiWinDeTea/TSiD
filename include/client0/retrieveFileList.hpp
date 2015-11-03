#ifndef RETRIEVEFILELIST_HPP_INCLUDED
#define RETRIEVEFILELIST_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <SFML/Network.hpp>
#include "../common/SCommand.hpp"
#include "../common/setColors.hpp"

/**
 * Retrieves and displays the files and folders available on the remote
 * @param  server            socket binded to the server
 * @param  current_directory working dircetory (remote)
 * @return                   true if the listing was possible, false otherwise
 */
bool retrieveFileList( sf::TcpSocket& server, std::string current_directory );

#endif
