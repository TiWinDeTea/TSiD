#ifndef S_READCONFIG_HPP_INCLUDED
#define S_READCONFIG_HPP_INCLUDED

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "s_createDirectory.hpp"
#include "s_Client.hpp"
#include "s_Config.hpp"
#include "setStdcinEcho.hpp"
#include "setColors.hpp"
#include "s_updateInformationsFiles.hpp"

/**
 * @brief   Reads the config
 * @details Searches for the following arguments :
 * - regen architecture
 * - new user at restart
 * - allow user creation
 * - allow private folder usage
 *
 * @return config containing some of the red parameters
 */
Config readConfig( unsigned short& port );

/**
 * Generates a default configuration with the following settings :
 *   - no architecture regeneration
 *   - no user creation at server restart
 *   - creation of new users by other users allowed
 *   - full private folders authorization
 * @return true if the config file could be generated
 */
bool generateDefaultConfig( unsigned short port );

/**
 * Creates the defaults folders
 */
void createArchitecture();

/**
 * Retrieve a user id and password to create them, and does so
 */
void getNewUser();

/**
 * Creates a new user
 * @param user_name id of the user to create
 * @param password  password of the user to create
 */
void newUser( std::string const& user_name, std::string const& password);

/**
 * applies immediate config choices (create a user at restart, …) and sets vars for the server general config (allow/disallow stuff)
 * @param l_arg   name of the config argument (left part of the config's line)
 * @param l_value value of the config argument (expected : "true" or "false" ; values different than "true" are interpreted false)
 * @param config  boolean array used to create the Config
 * @return        l_value or reset config value (eg : regen architecture is done only once, so it is to false after using it)
 */
std::string switchConfig( std::string const& l_arg, std::string const& l_value, bool config[CONFIG_SIZE] );

#endif
