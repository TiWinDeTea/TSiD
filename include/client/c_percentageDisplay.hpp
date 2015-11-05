#ifndef PERCENTAGEDISPLAY_HPP_INCLUDED
#define PERCENTAGEDISPLAY_HPP_INCLUDED

#include <iostream>
#include <iomanip>
#include "c_getConsoleWidth.hpp"
#include "setColors.hpp"

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

/**
 * displays the 'pacman percentage'
 * @param size       length for pacman's line
 * @param percentage percentage to display
 * @return
 */
void displayPacman( unsigned short size, unsigned char percentage );

/**
 * @brief resizes a string to a given size
 * If the size requested is shorter than the size of the string, "..." will be placed at the end of the generated string. Otherwise, spaces will be added until the string's size is 'size'
 * @param str  string to resize
 * @param size the size requested for the string
 */
void resize( std::string& str, unsigned int size );

#endif
