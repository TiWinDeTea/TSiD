#ifndef S_READCONFIG_HPP_INCLUDED
#define S_READCONFIG_HPP_INCLUDED

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "s_createDirectory.hpp"
#include "s_Client.hpp"
#include "s_Config.hpp"
#include "setStdcinEcho.hpp"

Config readConfig();
void generateDefaultConfig();
void createArchitecture();
void getNewUser();
void newUser( std::string const& user_name, std::string const& password);
std::string switchConfig( std::string const& l_arg, std::string const& l_value );
bool configSetter( std::string arg, int& pos );

#endif
