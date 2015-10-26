#ifndef DOWNLOAD_HPP_INCLUDED
#define DOWNLOAD_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "../common/SCommand.hpp"
#include "../common/fileExist.hpp"
#include "tcout.hpp"
#include "Client.hpp"

bool retrieveData( Client& client );

#endif
