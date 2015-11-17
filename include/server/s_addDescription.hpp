#ifndef S_ADDDESCRIPTION_HPP_INCLUDED
#define S_ADDDESCRIPTION_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <stdio.h>
#include "s_Client.hpp"
#include "s_tprint.hpp"
#include "fileExist.hpp"

/**
 * @brief Add a desription in the description file of the file in path
 * 
 * @param client The Client object wich contain the path of the file to add description, and the username for permission
 * @param description The description of the file
 * 
 * @return FileDoesNotExist if the description file doesn't exist,
 * NotAuthorized if the user doesn't have th permission to change the description,
 * UnknownIssue in case of error,
 * Success in case of success
 */
char addDescription(Client& client, std::string description);

#endif
