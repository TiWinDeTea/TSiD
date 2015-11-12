#ifndef C_USERINPUTINTERPRET_HPP_INCLUDED
#define C_USERINPUTINTERPRET_HPP_INCLUDED

#include <iostream>
#include "c_download.hpp"
#include "c_retrieveFileList.hpp"
#include "c_upload.hpp"
#include "c_moveToDirectory.hpp"
#include "c_createDirectory.hpp"
#include "c_passwd.hpp"
#include "c_help.hpp"

/**
 * Interprets the commands typed by the client
 * @param server  socket binded to the server
 * @param user_id user identifier on the server
 */
void userInputInterpret( sf::TcpSocket& server, std::string user_id );

#endif
