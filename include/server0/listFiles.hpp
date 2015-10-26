#ifndef LISTFILES_HPP_INCLUDED
#define LISTFILES_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <dirent.h>
#include <iostream>
#include "../common/SCommand.hpp"
#include "../common/isFolder.hpp"
#include "Client.hpp"

#ifndef WIN32
	#include <sys/types.h>
#endif

bool listFiles( Client& client );

#endif
