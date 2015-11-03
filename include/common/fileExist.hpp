#ifndef FILEEXIST_HPP_INCLUDED
#define FILEEXIST_HPP_INCLUDED

#include <fstream>

/**
 * tells if a file exists or not
 * @param  filename path to the file
 * @return          true if the file exist and could be opened, false otherwise+
 */
bool fileExist( std::string filename );

#endif
