#ifndef SETSTDCINECHO_HPP_INCLUDED
#define SETSTDCINECHO_HPP_INCLUDED

#ifdef _WIN32
	#include <windows.h>
	#include <WinNT.h>
#else
	#include <termios.h>
	#include <unistd.h>
#endif

void setStdcinEcho(bool enable);

#endif
