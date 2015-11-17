#ifndef C_CREATELOCALDIRECTORY_HPP_INCLUDED
#define C_CREATELOCALDIRECTORY_HPP_INCLUDED

#include <dirent.h>
#include "isFolder.hpp"

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#	define OS_WINDOWS
#	include <windows.h>
#else
#	include <sys/stat.h>
#endif

/**
 * @brief Create a directory
 * 
 * @param path The path of the directory to create
 * @return Created in case of success,
 * AlreadyExist if the directory already exist,
 * UnknownIssue in case of error
 */
bool createDirectory(std::string path);

#endif
