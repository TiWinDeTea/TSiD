#ifndef CREATEFILE_HPP_INCLUDED
#define CREATEFILE_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <stdio.h>
#include "tprint.hpp"
#include "../common/fileExist.hpp"
#include "../common/SCommand.hpp"

/**
 * @brief Create a file
 * 
 * @param path The path of the file to create
 * @return Created in case of success,
 * AlreadyExist if the file already exist,
 * UnknownIssue in case of error
 */
char createFile(std::string path);

#endif