#ifndef C_RETRIEVEFILELIST_HPP_INCLUDED
#define C_RETRIEVEFILELIST_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <SFML/Network.hpp>
#include "c_serverAnsInterpret.hpp"
#include "SCommand.hpp"
#include "setColors.hpp"

/**
 * Retrieves and displays the files and folders available on the remote
 * @param  server            socket binded to the server
 * @param  current_directory working dircetory (remote)
 * @return                   true if the listing was possible, false otherwise
 */
bool retrieveFileList( sf::TcpSocket& server, std::string current_directory );

/**
 * Formats the retrieved files and folders to a readable format.
 * Files and folders should be passed with this format : <filename>|<date>|<creator>
 * @param file          string to format
 * @param max_file_size size of the longest file
 */
void formatFilesDisplay( std::string& file, size_t max_file_size );

#endif
