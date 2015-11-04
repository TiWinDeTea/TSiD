#ifndef FORMATDIRECTORYPATH_HPP_INCLUDED
#define FORMATDIRECTORYPATH_HPP_INCLUDED

#include <fstream>
#include <string>
#include "../common/SCommand.hpp"
#include "Client.hpp"

/**
 * @brief format the path send by the client
 * @details If the path start with '/Private' add '/username' before the rest of the path,
 * else add '/Public' at the begenning, and finally add '.' at the begenning of the path
 * 
 * @param client The Client object wich contain the path
 */
void formatDirectoryPath(Client& client);

#endif
