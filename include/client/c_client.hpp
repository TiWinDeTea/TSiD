#ifndef C_CLIENT_HPP_INCLUDED
#define C_CLIENT_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include "c_userInputInterpret.hpp"
#include "c_serverAnsInterpret.hpp"
#include "setStdcinEcho.hpp"
#include "setColors.hpp"

bool sconnect( sf::TcpSocket& socket, std::string& user_id );
int main();

#endif
