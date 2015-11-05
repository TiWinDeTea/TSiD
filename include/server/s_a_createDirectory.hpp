#ifndef A_CREATEDIRECTORY_HPP_INCLUDED
#define A_CREATEDIRECTORY_HPP_INCLUDED

#include <SFML/Network.hpp>
#include "SCommand.hpp"
#include "s_Client.hpp"
#include "s_tprint.hpp"
#include "s_createDirectory.hpp"
#include "s_createInformationFile.hpp"

/**
 * @brief Answer to the client command 'mkdir'
 * 
 * @param client The Client object wich contain the path of the directory
 */
void a_createDirectory(Client& client);

#endif
