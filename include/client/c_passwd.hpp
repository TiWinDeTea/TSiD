#ifndef C_PASSWD_INCLUDED
#define C_PASSWD_INCLUDED

#include <iostream>
#include <SFML/Network.hpp>
#include "SCommand.hpp"
#include "setStdcinEcho.hpp"
#include "c_serverAnsInterpret.hpp"

/**
 * Changes the user password
 * @param server socket binded to the server
 */
void passwd( sf::TcpSocket& server );

#endif
