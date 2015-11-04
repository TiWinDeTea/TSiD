#ifndef CREATEDIRECTORY_HPP_INCLUDED
#define CREATEDIRECTORY_HPP_INCLUDED

#include <dirent.h>
#include "Client.hpp"
#include "tprint.hpp"

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
char createDirectory(std::string path);

#endif
