#ifndef SET_COLORS_HPP_INCLUDED
#define SET_COLORS_HPP_INCLUDED

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#	define OS_WINDOWS
#	include <windows.h>
#else
#	include <unistd.h>
#	include <iostream>
#endif

#include <string>

/**
 * Sets a display color in the terminal
 * @param text_color color to display ( values are : reset, black, blue, green, cyan, red, magenta, yellow, white, grey, and their 'light')
 */
void setColors( std::string const& text_color );

#endif
