#ifndef A_LISTFILES_HPP_INCLUDED
#define A_LISTFILES_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <dirent.h>
#include <iostream>
#include "../common/SCommand.hpp"
#include "tprint.hpp"
#include "../common/isFolder.hpp"
#include "Client.hpp"

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#else
	#include <sys/types.h>
#endif

bool a_listFiles( Client& client );

#endif
