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

char createNewUser( std::string const& user_name, std::string const& password );

#endif