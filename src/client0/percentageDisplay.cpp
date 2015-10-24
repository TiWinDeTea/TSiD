#include "../../include/client0/percentageDisplay.hpp"

void approxDisplay( unsigned int numb ){

	std::setprecision( 2 );
	std::cout << std::showpoint;

	if( numb >= (1024*1024) ){

		std::cout << std::setw( 4 ) << static_cast<double>(numb) / (1024*1024) << " MiB";
	} else if( numb >= 1024 ){

		std::cout << std::setw( 4 ) << static_cast<double>(numb) / 1024 << " KiB";
	} else std::cout << std::setw( 4 ) << numb << " B";

	std::setprecision( 6 );
	std::cout << std::showpoint;
}

void percentageDisplay( unsigned char percentage, std::string filename, unsigned int filesize, unsigned int alreadygot ){

	std::cout << std::flush << ' ' << filename << "  -  ";
	approxDisplay( filesize );
	std::cout << "\t\t";
	approxDisplay (alreadygot );
	std::cout << termcolor::cyan << " ["; 

	bool was_displayed(false);

	for( unsigned char i(0) ; i < 50 ; ++i){

		if( i >= static_cast<unsigned char>(percentage/2) ){

			if( !was_displayed ){
				
				was_displayed = true;
				if( i%2 == 0 )
					std::cout << termcolor::yellow << 'c';
				else std::cout << termcolor::yellow << 'C';
			}

			switch( i%4 ){

			case 0:
				std::cout << ' ';
				break;

			case 1:
				std::cout << termcolor::cyan << 'o';
				break;

			case 2:
				std::cout << ' ';
				break;

			case 3:
				std::cout << termcolor::cyan << 'O';
				break;

			default:;

			}

		} else std::cout << termcolor::cyan << '-';

	}

	std::cout << termcolor::cyan << "]  \r" << termcolor::reset;
}
