#ifndef IS_FOLDER_HPP_INCLUDED
#define IS_FOLDER_HPP_INCLUDED

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#	define OS_WINDOWS
#	include <windows.h>
#else
#	include <unistd.h>
#	include <iostream>
#	include <sys/stat.h> 
#endif

#include <string>
#include "../../include/common/fileExist.hpp"

/**
 * Tells if a given path leads to a folder or not
 * @param  path path to check
 * @return      true if the path leads to a folder, false otherwise
 */
bool isFolder(std::string const& path);

#endif