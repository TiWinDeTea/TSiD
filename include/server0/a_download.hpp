#ifndef A_DOWNLOAD_HPP_INCLUDED
#define A_DOWNLOAD_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "../common/SCommand.hpp"
#include "../common/fileExist.hpp"
#include "createFile.hpp"
#include "tprint.hpp"
#include "Client.hpp"
#include "WriteFileInformations.hpp"

bool a_retrieveData( Client& client );

#endif
