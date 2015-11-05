#ifndef S_SERVER_INCLUDED
#define S_SERVER_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include "SCommand.hpp"
#include "s_a_upload.hpp"
#include "s_a_download.hpp"
#include "s_a_listFiles.hpp"
#include "s_Client.hpp"
#include "s_formatDirectoryPath.hpp"
#include "s_a_directoryExist.hpp"
#include "s_a_createDirectory.hpp"
#include "s_tprint.hpp"
#include "s_readConfig.hpp"

void clientLoop(Client* client);
int main();

#endif
