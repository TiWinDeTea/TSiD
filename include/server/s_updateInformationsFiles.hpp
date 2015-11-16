#ifndef S_UPDATEINFORMATIONSFILES_HPP_INCLUDED
#define S_UPDATEINFORMATIONSFILES_HPP_INCLUDED

#include <iostream>
#include <dirent.h>
#include "isFolder.hpp"
#include "s_createInformationFile.hpp"

/**
 * @brief Create all the informations files wich doesn't exist
 * 
 * @param path path to the folder to update
 */
void updateInformationsFiles(std::string path);

#endif
