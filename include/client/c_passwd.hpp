#ifndef C_PASSWD_INCLUDED
#define C_PASSWD_INCLUDED

#include <iostream>
#include <SFML/Network.hpp>
#include "SCommand.hpp"
#include "setStdcinEcho.hpp"
#include "c_serverAnsInterpret.hpp"

void passwd( sf::TcpSocket& server );

#endif
