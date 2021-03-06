#ifndef S_CREATEFILE_HPP_INCLUDED
#define S_CREATEFILE_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <stdio.h>
#include "s_tprint.hpp"
#include "fileExist.hpp"
#include "SCommand.hpp"

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
