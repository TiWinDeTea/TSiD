#include "include/client0/percentageDisplay.hpp"

void approxDisplay( unsigned int numb ){

	std::setprecision( 2 );
	std::cout << std::showpoint;

	if( numb > 1024*1024 ){
		
		std::cout << std::setw( 6 ) << static_cast<double>( (10*numb)/(1024*1024) )/10 << " MiB";
	} else if( numb > 1024 ){

		std::cout << std::setw( 6 ) << static_cast<double>( (10*numb)/1024 )/10 << " KiB";
	} else std::cout << std::setw( 6 ) << numb << " B";

	std::setprecision( 6 );
	std::cout << std::showpoint;
}

void percentageDisplay( unsigned char percentage, std::string filename, unsigned int filesize, unsigned int alreadygot=0 ){

	if( alreadygot == 0)
		alreadygot=filesize;

	std::cout << std::flush << ' ' << filename << "  -  ";
	approxDisplay( filesize );
	std::cout << "\t\t";
	approxDisplay (alreadygot );
	std::cout << " [";

	bool was_displayed(false);

	for( unsigned char i(0) ; i < 50 ; ++i){

		if( i >= static_cast<unsigned char>(percentage/2) ){
			
			if( !was_displayed ){
				
				was_displayed = true;
				if( i%2 == 0 )
					std::cout << 'c';
				else std::cout << 'C';
			}

			switch( i%4 ){

			case 0:
				std::cout << ' ';
				break;

			case 1:
				std::cout << 'o';
				break;

			case 2:
				std::cout << ' ';
				break;

			case 3:
				std::cout << 'O';
				break;

			default:;

			}

		} else std::cout << '-';

	}

	std::cout << "]  \r";
}
