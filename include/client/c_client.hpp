#ifndef C_CLIENT_HPP_INCLUDED
#define C_CLIENT_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include "c_preferences.hpp"
#include "c_userInputInterpret.hpp"
#include "c_serverAnsInterpret.hpp"
#include "c_getServerMessage.hpp"
#include "setStdcinEcho.hpp"
#include "setColors.hpp"

/**
 * Connect the client to the server, sending his/her id and password.
 * @param socket  socket that will be connected to the server
 * @param user_id client's id
 * @return        true if the connection was successful, false otherwise
 */
bool sconnect( sf::TcpSocket& socket, std::string& user_id );

/**
 * main function. Connects the user to a server and wait for user command inputs
 * @return EXIT_SUCCESS if user asked for a disconnection, EXIT_FAILURE if connection to server was unsuccessful
 */
int main();

#endif
