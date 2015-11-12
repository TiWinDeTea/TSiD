#ifndef S_SERVER_INCLUDED
#define S_SERVER_INCLUDED

#include <SFML/Network.hpp>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <functional>
#include "SCommand.hpp"
#include "s_a_upload.hpp"
#include "s_a_download.hpp"
#include "s_a_listFiles.hpp"
#include "s_Client.hpp"
#include "s_formatDirectoryPath.hpp"
#include "s_a_directoryExist.hpp"
#include "s_a_createDirectory.hpp"
#include "s_a_changePassword.hpp"
#include "s_tprint.hpp"
#include "s_readConfig.hpp"

/**
 * @brief Lauch the loop waiting for client command ans calling the corresponding functions
 * 
 * @param client The Client object wich contain the socket to receive the client commands,
 * and send the answers
 */
void clientLoop(Client* client, Config* config);

/**
 * @brief The main, read the config, listen for new client and launch a thread of each of new client.
 * @return EXIT_FAILURE if the listener failed to listen,
 * else never end
 */
int main();

#endif
