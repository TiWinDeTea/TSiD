#ifndef PERCENTAGEDISPLAY_HPP_INCLUDED
#define PERCENTAGEDISPLAY_HPP_INCLUDED

#include <iostream>
#include <iomanip>
#include "../common/setColors.hpp"

void approxDisplay( unsigned int numb );
void percentageDisplay( unsigned char percentage, std::string filename, unsigned int filesize, unsigned int alreadygot );

#endif
