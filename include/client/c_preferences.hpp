#ifndef C_LOADPREFERENCES_HPP_INCLUDED
#define C_LOADPREFERENCES_HPP_INCLUDED

#include <fstream>
#include <iostream>

/**
 * Loads the previous server's address, port, and used username.
 * @return true if successfuly loaded and the guy want to use them, false otherwise
 */
bool loadPreferences( std::string& user_name, std::string& ip_address, unsigned short& port );

/**
 * Writes the above
 * @return true if successful, false otherwise
 */
bool writePreferences( std::string const& user_name, std::string const& ip_address, unsigned short port );


#endif
