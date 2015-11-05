#ifndef UPLOAD_HPP_INCLUDED
#define UPLOAD_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include "c_percentageDisplay.hpp"
#include "c_serverAnsInterpret.hpp"
#include "c_formatPath.hpp"
#include "SCommand.hpp"
#include "getFileLength.hpp"
#include "isFolder.hpp"

#if defined(WIN32) || defined(WIN64) || defined(_WIN32) || defined(_WIN64)
#else
#include <sys/types.h>
#endif

#define NB_BYTE_PER_PACKET 8192

/**
 * \brief starts the upload of a single file
 * Starts the upload by sending its size, name, destination file to the server. The file itself is not sent tho
 * @param  infile    ifstream containing the file to be sent. It is being opened
 * @param  file_size size of the file. It is set in this func. Required to upload later on.
 * @param  server    socket binded to the server
 * @param  directory working directory (remote)
 * @param  filename  path to the file (local)
 * @return           true if it succesfully initialized the upload, false otherwise.
 */
bool startUpload( std::ifstream& infile, unsigned int& file_size, sf::TcpSocket& server, std::string const& directory, std::string filename );

/**
 * Initialize the upload (delagating the work to the right func)
 * @param  server            socket binded to the server
 * @param  current_directory working directory (on the remote)
 * @return                   true if the file was retrieved successfully, false otherwise
 */
bool sendData( sf::TcpSocket& server, std::string const& current_directory );

/**
 * Uploads a single file
 * @param  server           socket binded to the server
 * @param  input_file       ifstream to the file to upload. must be already opened.
 * @param  filesize         size of the file to download
 * @param  filename         downloaded file name (for display purposes)
 * @return                  true if the upload was successful, false otherwise
 */
bool uploadFile( sf::TcpSocket& server, std::ifstream& input_file, unsigned int file_size, std::string const& filename );

/**
 * Recursively upload files (used to upload a whole folder)
 * @param  server            socket binded to the server
 * @param  remote_directory  working directory (remote)
 * @param  current_directory working directory (local)
 * @param  folder_name       folder to upload
 * @return                   true if every upload was successful, false otherwise
 * \todo                     debugging server answer (maybe it is on server's side)
 */
bool recursiveUpload( sf::TcpSocket& server, std::string remote_directory, std::string current_directory, std::string folder_name );

#endif
