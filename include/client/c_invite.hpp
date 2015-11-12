#ifndef C_INVITE_HPP_INCLUDED
#define C_INVITE_HPP_INCLUDED

#include <iostream>
#include <SFML/Network.hpp>
#include "setStdcinEcho.hpp"
#include "SCommand.hpp"
#include "c_serverAnsInterpret.hpp"

/**
 * Creates a new user on the server
 * @param server A socket binded to the server
 * @return       true if successful, false otherwise
 */
bool invite( sf::TcpSocket& server );

#endif
