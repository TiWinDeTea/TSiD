#ifndef A_UPLOAD_HPP_INCLUDED
#define A_UPLOAD_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include "../common/SCommand.hpp"
#include "../common/fileExist.hpp"
#include "../common/getFileLength.hpp"
#include "tprint.hpp"
#include "Client.hpp"

#define NB_BYTE_PER_PACKET 8192

/**
 * @brief Answer to the client command 'get'
 * @details send the file size, the number of bytes per packet and upload the file to the client
 * 
 * @param client The Client object wich contain the path of the file to upload
 * @return 1 for fail, 0 for success
 */
bool a_sendData( Client& client );

#endif
