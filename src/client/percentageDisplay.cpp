#include "c_percentageDisplay.hpp"

void approxDisplay( unsigned int numb ){

	if( numb >= (1024*1024) ){

		std::cout << std::setw( 4 ) << static_cast<int>(numb / (1024*1024)) << " MiB";
	} else if( numb >= 1024 ){

		std::cout << std::setw( 4 ) << static_cast<int>(numb / 1024) << " KiB";
	} else std::cout << std::setw( 4 ) << numb << " B";
}

void percentageDisplay( unsigned char percentage, std::string filename, unsigned int filesize, unsigned int alreadygot ){

	unsigned int columns( getConsoleWidth() );
	std::cout << std::flush ;

	if( columns < 3 )
		return;

	if( columns <= 10 ){

		setColors("red");
		for( unsigned char i(0) ; i< columns ; ++i )
			std::cout << "—";
		std::cout << '\r';
		setColors("reset");
		return;
	}//else

	std::cout << ' ';

	if( columns <= 34 ){

		resize( filename, columns - 10 );
		std::cout << filename << ' ';
		approxDisplay( alreadygot );
		std::cout << '\r';
		return;
	}//else

	if( columns <= 45 ){

		resize( filename, columns - 19 );
		std::cout << filename << ' ';
		approxDisplay( alreadygot );
		std::cout << '/';
		approxDisplay( filesize );
		std::cout << '\r';
		return;
	}//else

	unsigned short pacman_size( static_cast<unsigned short>(columns - 45) );
	if( columns/3 < pacman_size )
		pacman_size = static_cast<unsigned short>(columns/3 );

	resize( filename, columns - pacman_size - 20 );
	std::cout << filename << ' ';
	approxDisplay( alreadygot );
	std::cout << '/';
	approxDisplay( filesize );
	displayPacman( pacman_size, percentage );
	std::cout << '\r';

}

void displayPacman( unsigned short size, unsigned char percentage ){

	if( size < 5)
		return;
	setColors("cyan");
	std::cout << " ["; 

	bool was_displayed(false);

	for( unsigned char i(0) ; i < size-3 ; ++i){

		if( i >= static_cast<unsigned char>(percentage * (size-2) / 100) ){

			if( !was_displayed ){
				
				was_displayed = true;
				setColors("yellow");
				if( i%2 == 0 )
					std::cout << 'c';
				else std::cout << 'C';
			}

			switch( i%4 ){

			case 0:
				std::cout << ' ';
				break;
			case 1:
				setColors("cyan");
				std::cout << 'o';
				break;

			case 2:
				std::cout << ' ';
				break;

			case 3:
				setColors("cyan");
				std::cout << 'O';
				break;

			default:;

			}

		} else {
			
			setColors("cyan");
			std::cout << '-';
		}

	}

	setColors("cyan");
	std::cout << ']';
	setColors("reset");
}

void resize( std::string& str, unsigned int size ){

	if( str.size() == size )
		return;

	if( str.size() < size ){

		for( unsigned int i( static_cast<unsigned int>(str.size()) ) ; i<size ; ++i ){
			str+=' ';
		}
	}
	else{
		if( size < 3 )
			str=".";
		else{
			str.erase( size - 3 );
			str+="...";
		}
	}
	
}
