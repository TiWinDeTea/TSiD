#ifndef GET_CONSOLE_WIDTH_HPP_INCLUDED
#define GET_CONSOLE_WIDTH_HPP_INCLUDED

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
	#include <windows.h>
	#define OS_WINDOWS
#else
	#include <unistd.h>
	#include <sys/ioctl.h>
#endif

/**
 * Used to retrieve the width of the display console
 * @return width of the console
 */
unsigned int getConsoleWidth();




#endif
