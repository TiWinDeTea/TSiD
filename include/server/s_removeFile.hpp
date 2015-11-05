#ifndef REMOVEFILE_HPP_INCLUDED
#define REMOVEFILE_HPP_INCLUDED

#include <iostream>
#include <stdio.h>
#include "s_tprint.hpp"
#include "fileExist.hpp"
#include "SCommand.hpp"

/**
 * @brief Remove a file
 * 
 * @param path The path of the file to remove
 * @return Succes in case of success,
 * FileDoesNotExist if the file doesn't exist,
 * UnknownIssue in case of error
 */
char removeFile(std::string path);

#endif