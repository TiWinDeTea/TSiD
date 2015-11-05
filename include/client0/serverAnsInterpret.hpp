#ifndef SERVERANSINTERPRETER_HPP_INCLUDED
#define SERVERANSINTERPRETER_HPP_INCLUDED

#include "../common/SCommand.hpp"
#include <iostream>

/**
 * Interprets the answer of the server and display in consequence (just a switch)
 * @param  sanswer answer given by the server
 * @return         true if the answer is positive, false otherwise
 */
bool interpretServerAns( signed char sanswer );								//Sends message to console telling the problem // success
bool tMutedServerInterpret( signed char sanswer );

#endif
