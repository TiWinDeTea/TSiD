#ifndef DIRECTORYEXIST_HPP_INCLUDED
#define DIRECTORYEXIST_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <dirent.h>
#include "../common/SCommand.hpp"
#include "Client.hpp"
#include "tprint.hpp"

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#else
	#include <sys/types.h>
#endif

void directoryExist(Client& client);

#endif
