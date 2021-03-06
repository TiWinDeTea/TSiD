#ifndef S_A_DOWNLOAD_HPP_INCLUDED
#define S_A_DOWNLOAD_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "SCommand.hpp"
#include "fileExist.hpp"
#include "s_createFile.hpp"
#include "s_removeFile.hpp"
#include "s_tprint.hpp"
#include "s_Client.hpp"
#include "s_createInformationFile.hpp"

/**
 * @brief Answer to the client command 'put'
 * @details receive the file size, the number of bytes per packet and download the file from the client
 * 
 * @param client The Client object wich contain the path of the file to download
 * @return 1 for fail, 0 for success
 */
bool a_retrieveData( Client& client );

#endif
