#ifndef S_A_CREATENEWUSER_HPP_INCLUDED
#define S_A_CREATENEWUSER_HPP_INCLUDED

#include <SFML/Network.hpp>
#include "SCommand.hpp"
#include "s_Client.hpp"
#include "s_tprint.hpp"
#include "fileExist.hpp"
#include "s_createNewUser.hpp"
#include "s_tprint.hpp"

/**
 * @brief answer to the client command 'invite'
 * @details call the function 'createNewUser'
 * 
 * @param client The Client object which contain the socket and packet
 * @return true for success,
 * false for error
 */
bool a_createNewUser(Client& client);

#endif
