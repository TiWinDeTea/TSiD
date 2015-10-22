#ifndef USERINPUTINTERPRET_HPP_INCLUDED
#define USERINPUTINTERPRET_HPP_INCLUDED

#include <iostream>
#include "../client0/download.hpp"
#include "../client0/retrieveFileList.hpp"
#include "../client0/upload.hpp"
#include "../client0/moveToDirectory.hpp"

void userInputInterpret( sf::TcpSocket& server, std::string user_id );

#endif
