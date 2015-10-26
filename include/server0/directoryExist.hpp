#ifndef DIRECTORYEXIST_HPP_INCLUDED
#define DIRECTORYEXIST_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <dirent.h>
#include "../common/SCommand.hpp"
#include "Client.hpp"
#include "tcout.hpp"

#ifndef WIN32
	#include <sys/types.h>
#endif

void directoryExist(Client& client);

#endif
