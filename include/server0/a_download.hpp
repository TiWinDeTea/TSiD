#ifndef A_DOWNLOAD_HPP_INCLUDED
#define A_DOWNLOAD_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "../common/SCommand.hpp"
#include "../common/fileExist.hpp"
#include "createFile.hpp"
#include "tprint.hpp"
#include "Client.hpp"
#include "writeFileInformations.hpp"

/**
 * @brief Answer to the client command 'put'
 * @details receive the file size, the number of bytes per packet and download the file from the client
 * 
 * @param client The Client object wich contain the path of the file to download
 * @return 1 for fail, 0 for success
 */
bool a_retrieveData( Client& client );

#endif
