#ifndef S_CREATENEWUSER_HPP_INCLUDED
#define S_CREATENEWUSER_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <locale>
#include "s_tprint.hpp"
#include "fileExist.hpp"
#include "s_createFile.hpp"
#include "s_createDirectory.hpp"
#include "s_removeFile.hpp"
#include "SCommand.hpp"

/**
 * @brief Create a new user
 * @details create the file "UsersData/"+user_name with the password inside;
 * create directory "Private/"+user_name
 * create directory "FilesData/Private/"+user_name
 * 
 * @param user_name The user name
 * @param password The user password
 * 
 * @return Success in case of success,
 * AlreadyExist if the user already exist,
 * UnknownIssue in case of error
 */
char createNewUser( std::string const& user_name, std::string const& password );

#endif