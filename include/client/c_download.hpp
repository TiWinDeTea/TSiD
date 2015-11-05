#ifndef DOWNLOAD_HPP_INCLUDED
#define DOWNLOAD_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "SCommand.hpp"
#include "fileExist.hpp"
#include "c_serverAnsInterpret.hpp"
#include "c_formatPath.hpp"
#include "c_percentageDisplay.hpp"

/**
 * \brief starts the download of a single file
 * Starts the download by retriving its size, name, destination file to the server. The file itself is not downloaded tho
 * @param  server           A socket binded to the server. Must be already connected.
 * @param  spacket          Generic sf::packet
 * @param  filesize         File size is used to return the size of the file back to the calling function. It is required to download later onS.
 * @param  bytes_per_packet Used to return the number of bytes that the server should send with each packet. Required to download.
 * @param  output_file      Ofstream binded to the output file. It is only openened in this func.
 * @param  directory        The directory where the file is being downloaded from (remote dir)
 * @param  filename         Path to the file
 * @return                  true if it succesfully initialized the download, false otherwise.
 */
bool startDownload( sf::TcpSocket& server, sf::Packet& spacket, unsigned int& filesize, unsigned int& bytes_per_packet, std::ofstream& output_file, std::string& directory, std::string filename );

/**
 * Initialize the download (delagating the work to the right func)
 * @param  server            socket binded to the server
 * @param  current_directory working directory (on the remote)
 * @return                   true if the file was retrieved successfully, false otherwise
 */
bool retrieveData( sf::TcpSocket& server, std::string current_directory );

/**
 * Downloads a single file
 * @param  server           socket binded to the server
 * @param  spacket          generic sf::Packet
 * @param  filesize         size of the file to download
 * @param  bytes_per_packet number of bytes retrieved with each packet
 * @param  output_file      ofstream binded to the output file
 * @param  filename         downloaded file name (for display purposes)
 * @return                  true if the download was successful, false otherwise
 */
bool downloadFile( sf::TcpSocket& server, sf::Packet& spacket, unsigned int filesize, unsigned int bytes_per_packet, std::ofstream& output_file, std::string const& filename);

/**
 * Download files recursively (used to download a folder)
 * @param  server           socket binded to the server
 * @param  remote_directory directory to be downloaded
 * @return                  true if every download was successful, false otherwise
 * \todo                                     everything
 */
bool recursiveDownload( sf::TcpSocket& server, std::string remote_directory );

#endif
