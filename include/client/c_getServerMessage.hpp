#ifndef C_GETSERVERMESSAGE_INCLUDED
#define C_GETSERVERMESSAGE_INCLUDED

#include <iostream>
#include <SFML/Network.hpp>
#include <sstream>
#include "setColors.hpp"
#include "c_serverAnsInterpret.hpp"

/**
 * Retrieves the server's message of the day and displays it with colors
 * @param server A socket binded to the server
 */
void getServerMessage( sf::TcpSocket& server );

#endif
