#ifndef LISTFILES_HPP_INCLUDED
#define LISTFILES_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <dirent.h>
#include <iostream>
#include "../common/SCommand.hpp"
#include "tcout.hpp"
#include "../common/isFolder.hpp"
#include "Client.hpp"

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#else
	#include <sys/types.h>
#endif

bool listFiles( Client& client );

#endif
