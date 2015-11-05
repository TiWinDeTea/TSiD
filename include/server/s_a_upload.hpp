#ifndef S_A_UPLOAD_HPP_INCLUDED
#define S_A_UPLOAD_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include "SCommand.hpp"
#include "fileExist.hpp"
#include "getFileLength.hpp"
#include "s_tprint.hpp"
#include "s_Client.hpp"

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
