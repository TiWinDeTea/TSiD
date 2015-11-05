#include "c_getConsoleWidth.hpp"

unsigned int getConsoleWidth(){

#ifdef OS_WINDOWS

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &csbi );

	return csbi.srWindow.Right - csbi.srWindow.Left;
#else
	
	struct winsize ws;
	ioctl( STDOUT_FILENO, TIOCGWINSZ, &ws );

	return ws.ws_col;

#endif
}
