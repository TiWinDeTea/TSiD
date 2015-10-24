#ifndef SETSTDCINECHO_HPP_INCLUDED
#define SETSTDCINECHO_HPP_INCLUDED

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
	#include <windows.h>
	#include <WinNT.h>
#else
	#include <termios.h>
	#include <unistd.h>
#endif

void setStdcinEcho(bool enable);

#endif
