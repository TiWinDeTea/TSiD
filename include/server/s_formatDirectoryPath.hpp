#ifndef FORMATDIRECTORYPATH_HPP_INCLUDED
#define FORMATDIRECTORYPATH_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include "SCommand.hpp"
#include "s_Client.hpp"

/**
 * @brief format the path send by the client
 * @details If the path contain '/..' return false,
 * else if the path start with '/Private' add '/username' before the rest of the path,
 * else add '/Public' at the begenning, and finally add '.' at the begenning of the path.
 * 
 * @param client The Client object wich contain the path
 * @return true if the path is correct,
 * false else
 */
bool formatDirectoryPath(Client& client);

#endif
