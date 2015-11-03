#ifndef PERCENTAGEDISPLAY_HPP_INCLUDED
#define PERCENTAGEDISPLAY_HPP_INCLUDED

#include <iostream>
#include <iomanip>
#include "../common/setColors.hpp"

/**
 * displays a number of bytes casting it in MiB, KiB, or B. Also sets a constant space usage
 * @param numb number to be displayed
 */
void approxDisplay( unsigned int numb );

/**
 * displays a percentage with the 'pacman' style
 * @param percentage percentage to display
 * @param filename   name of the file being downloaded/uploaded
 * @param filesize   total size of the file (in bytes)
 * @param alreadygot number of bytes already transferred
 */
void percentageDisplay( unsigned char percentage, std::string filename, unsigned int filesize, unsigned int alreadygot );

#endif
