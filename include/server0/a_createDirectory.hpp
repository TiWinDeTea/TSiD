#ifndef A_CREATEDIRECTORY_HPP_INCLUDED
#define A_CREATEDIRECTORY_HPP_INCLUDED

#include <SFML/Network.hpp>
#include "../common/SCommand.hpp"
#include "Client.hpp"
#include "tprint.hpp"
#include "createDirectory.hpp"
#include "createInformationFile.hpp"

/**
 * @brief Answer to the client command 'mkdir'
 * 
 * @param client The Client object wich contain the path of the directory
 */
void a_createDirectory(Client& client);

#endif
