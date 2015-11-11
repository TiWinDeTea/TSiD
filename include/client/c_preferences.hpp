#ifndef C_LOADPREFERENCES_HPP_INCLUDED
#define C_LOADPREFERENCES_HPP_INCLUDED

#include <fstream>
#include <iostream>

bool loadPreferences( std::string& user_name, std::string& ip_address, unsigned short& port );
bool writePreferences( std::string const& user_name, std::string const& ip_address, unsigned short port );


#endif
