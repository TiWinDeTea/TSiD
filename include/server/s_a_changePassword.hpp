#ifndef S_A_CHANGEPASSWORD_HPP_INCLUDED
#define S_A_CHANGEPASSWORD_HPP_INCLUDED

#include <SFML/Network.hpp>
#include "SCommand.hpp"
#include "s_Client.hpp"
#include "s_tprint.hpp"

/**
 * @brief Answer to the client command 'passwd'
 * @details change the password of the client
 * 
 * @param client The Client object wich contain the username and the socket used in this function
 * @return 1 for fail, 0 for success
 */
bool a_changePassword(Client& client);

#endif
