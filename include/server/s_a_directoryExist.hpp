#ifndef A_DIRECTORYEXIST_HPP_INCLUDED
#define A_DIRECTORYEXIST_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <dirent.h>
#include "SCommand.hpp"
#include "s_Client.hpp"
#include "s_tprint.hpp"

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#else
	#include <sys/types.h>
#endif

/**
 * @brief Answer to the client command Exist (send by command 'cd')
 * 
 * @param client The Client object wich contain the path of the directory
 */
bool a_directoryExist(Client& client);

#endif
