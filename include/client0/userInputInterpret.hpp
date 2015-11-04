#ifndef USERINPUTINTERPRET_HPP_INCLUDED
#define USERINPUTINTERPRET_HPP_INCLUDED

#include <iostream>
#include "download.hpp"
#include "retrieveFileList.hpp"
#include "upload.hpp"
#include "moveToDirectory.hpp"
#include "createDirectory.hpp"

/**
 * Interprets the commands typed by the client
 * @param server  socket binded to the server
 * @param user_id user identifier on the server
 */
void userInputInterpret( sf::TcpSocket& server, std::string user_id );

#endif
