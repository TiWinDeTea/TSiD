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

char createDirectory(std::string path);

#endif
