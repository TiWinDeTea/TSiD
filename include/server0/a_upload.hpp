#ifndef A_UPLOAD_HPP_INCLUDED
#define A_UPLOAD_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include "../common/SCommand.hpp"
#include "../common/fileExist.hpp"
#include "../common/getFileLength.hpp"
#include "tprint.hpp"
#include "Client.hpp"

#define NB_BYTE_PER_PACKET 8192

bool a_sendData( Client& client );

#endif
