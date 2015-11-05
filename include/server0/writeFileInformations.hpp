#ifndef WRITEFILEINFORMATIONS_HPP_INCLUDED
#define WRITEFILEINFORMATIONS_HPP_INCLUDED

#include <iostream>
#include "../common/SCommand.hpp"
#include "../common/fileExist.hpp"
#include "../common/isFolder.hpp"
#include "Client.hpp"
#include "tprint.hpp"
#include "formatedTime.hpp"
#include "createDirectory.hpp"

/**
 * @brief Create the information file and write basic informations inside
 * @details Write the creations date on the first line,
 * the username of the client on the second line
 * 
 * @param client The Client object wich contain the path of the file, and the username of the client
 * @return Created in case of success,
 * AlreadyExist if the file already exist,
 * UnknownIssue in case of error
 */
char writeFileInformations(Client& client);

#endif
