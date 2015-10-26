#include "../../include/common/setColors.hpp"

void setColors( std::string const& text_color)
{

#ifdef OS_WINDOWS
	unsigned char output_color(15);				/**grey**/

	if( text_color == "reset" );				/**don't go through that**/
	else if( text_color == "black" )			output_color = 0;/**break**/
	else if( text_color == "blue" )				output_color = 1;/**break**/
	else if( text_color == "green" )			output_color = 2;/**break**/
	else if( text_color == "cyan" )				output_color = 3;/**break**/
	else if( text_color == "red" )				output_color = 4;/**break**/
	else if( text_color == "magenta" )			output_color = 5;/**break**/
	else if( text_color == "yellow" )			output_color = 6;/**break**/
	else if( text_color == "white" )			output_color = 7;/**break**/
	else if( text_color == "grey" )				output_color = 8;/**break**/
	else if( text_color == "light blue" )			output_color = 9;/**break**/
	else if( text_color == "light green" )			output_color = 10;/**break**/
	else if( text_color == "light cyan" )			output_color = 11;/**break**/
	else if( text_color == "light red" )			output_color = 12;/**break**/
	else if( text_color == "light magenta" )		output_color = 13;/**break**/
	else if( text_color == "light yellow" )			output_color = 14;/**break**/
	else if( text_color == "bright white" )			output_color = 15;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), output_color);
#else
	
	if( text_color == "reset" )					std::cout << "\033[97;1m" ;/**break**/
	else if( text_color == "black" )			std::cout << "\033[8m" ;/**break**/
	else if( text_color == "grey" )				std::cout << "\033[30m";/**break**/
	else if( text_color == "red" )				std::cout << "\033[31m";/**break**/
	else if( text_color == "green" )			std::cout << "\033[32m";/**break**/
	else if( text_color == "yellow" )			std::cout << "\033[33m";/**break**/
	else if( text_color == "blue" )				std::cout << "\033[34m";/**break**/
	else if( text_color == "magenta" )			std::cout << "\033[35m";/**break**/
	else if( text_color == "cyan" )				std::cout << "\033[36m";/**break**/
	else if( text_color == "white" )			std::cout << "\033[37m";/**break**/
	else if( text_color == "light red" )			std::cout << "\033[91m";/**break**/
	else if( text_color == "light green" )			std::cout << "\033[92m";/**break**/
	else if( text_color == "light yellow" )			std::cout << "\033[93m";/**break**/
	else if( text_color == "light blue" )			std::cout << "\033[94m";/**break**/
	else if( text_color == "light magenta" )		std::cout << "\033[95m";/**break**/
	else if( text_color == "light cyan" )			std::cout << "\033[96m";/**break**/
	else if( text_color == "bright white" )			std::cout << "\033[97m";

#endif
}
