#ifndef GETFILELENGTH_HPP_INCLUDED
#define GETFILELENGTH_HPP_INCLUDED

#include <fstream>

/**
 * Retrieves the size of a file (in bytes)
 * @param  filename file to study
 * @return          weight of the file (in bytes+)
 */
unsigned int getFileLength( std::string const& filename );

#endif
