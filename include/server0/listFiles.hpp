#ifndef LISTFILES_HPP_INCLUDED
#define LISTFILES_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <dirent.h>
#include <iostream>
#include "../common/SCommand.hpp"

#ifndef WIN32
	#include <sys/types.h>
#endif

#include "../../include/server0/Client.hpp"
bool listFiles( Client& client );

#endif
