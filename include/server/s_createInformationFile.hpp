#ifndef S_WRITEFILEINFORMATIONS_HPP_INCLUDED
#define S_WRITEFILEINFORMATIONS_HPP_INCLUDED

#include <iostream>
#include "SCommand.hpp"
#include "fileExist.hpp"
#include "isFolder.hpp"
#include "s_Client.hpp"
#include "s_tprint.hpp"
#include "s_formatedTime.hpp"
#include "s_createFile.hpp"
#include "s_createDirectory.hpp"

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
char createInformationFile(Client& client);

#endif
