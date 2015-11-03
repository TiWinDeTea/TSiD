#ifndef READCONFIG_HPP_INCLUDED
#define READCONFIG_HPP_INCLUDED

#include <iostream>
#include <sstream>
#include <fstream>
#include "createDirectory.hpp"
#include "../common/setStdcinEcho.hpp"

void readConfig();
void generateDefaultConfig();
void createArchitecture();
void getNewUser();
void newUser( std::string const& user_name, std::string const& password);
void switchConfig( std::string const& l_arg, std::string const& l_value );

#endif
