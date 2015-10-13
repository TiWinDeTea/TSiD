#ifndef SETSTDCINECHO_HPP_INCLUDED
#define SETSTDCINECHO_HPP_INCLUDED

#ifdef WIN32
	#include <IntSafe.h>
	#include <WinNT.h>
#else
	#include <termios.h>
	#include <unistd.h>
#endif

void setStdcinEcho(bool enable = true);

#endif
