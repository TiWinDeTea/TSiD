#ifndef USERINPUTINTERPRET_HPP_INCLUDED
#define USERINPUTINTERPRET_HPP_INCLUDED

#include <iostream>
#include "download.hpp"
#include "retrieveFileList.hpp"
#include "upload.hpp"
#include "moveToDirectory.hpp"

void userInputInterpret( sf::TcpSocket& server, std::string user_id );

#endif
