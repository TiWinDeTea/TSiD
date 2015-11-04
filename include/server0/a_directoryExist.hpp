#ifndef A_DIRECTORYEXIST_HPP_INCLUDED
#define A_DIRECTORYEXIST_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <dirent.h>
#include "../common/SCommand.hpp"
#include "Client.hpp"
#include "tprint.hpp"

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#else
	#include <sys/types.h>
#endif

/**
 * @brief Answer to the client command Exist (send by command 'cd')
 * 
 * @param client The Client object wich contain the path of the directory
 */
void a_directoryExist(Client& client);

#endif
