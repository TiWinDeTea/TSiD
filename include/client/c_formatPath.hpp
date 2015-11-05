#ifndef FORMAT_PATH_HPP_INCLUDED
#define FORMAT_PATH_HPP_INCLUDED

#include <string>

/**
 * returns the last part of a path (file)
 * @param  path path to be "formated"
 * @return      last part of the path
 */
std::string formatPath( std::string const& path );

/**
 * \brief formats a path
 * Revomes the eventuals "./././", interprets the "../", removes the eventuals "//////"
 * @param dir_path path to be formated
 */
void formatDir( std::string& dir_path );

#endif
