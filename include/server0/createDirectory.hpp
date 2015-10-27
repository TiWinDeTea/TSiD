#ifndef CREATEDIRECTORY_HPP_INCLUDED
#define CREATEDIRECTORY_HPP_INCLUDED

#include <SFML/Network.hpp>
#include "../common/SCommand.hpp"
#include "directoryExist.hpp"

#include "Client.hpp"
#include "tprint.hpp"

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#	define OS_WINDOWS
#	include <windows.h>
#else
#	include <sys/stat.h>
#endif

void createDirectory(Client& client);

#endif
