#ifndef S_FORMATED_WELCOMEMESSAGE_HPP_INCLUDED
#define S_FORMATED_WELCOMEMESSAGE_HPP_INCLUDED

#include <iostream>
#include <string>
#include <sstream>
#include "s_tprint.hpp"
#include "s_Client.hpp"
#include "s_formatedTime.hpp"

/**
 * @brief format the welcome message from WelcomeMessage.txt
 * 
 * @param message string to stock the message
 * @param client The client object with the username inside
 */
void formatedWelcomeMessage(std::string& message, Client& client);

#endif
