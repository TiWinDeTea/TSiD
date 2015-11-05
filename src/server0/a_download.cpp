#include "../../include/server0/a_download.hpp"

bool a_retrieveData(Client& client){

    unsigned int filesize;
    unsigned int bytes_per_packet;

    if( !(client.packet >> filesize >> bytes_per_packet) ){
        client.packet.clear();
        client.packet << UnknownIssue;
        client.socket.send(client.packet);
        tprint();
        std::cout << client.name() << " -> There was an error reading file infos" << std::endl;
        return false;
    }
    std::cout << "\t-File informations are ok" << std::endl;
    std::cout << "\t-File: " << client.path << std::endl;

    client.packet.clear();

    switch(createFile(client.path)){
        
        case AlreadyExist:
            client.packet << AlreadyExist;
            client.socket.send(client.packet);
            tprint();
            std::cout << client.name() << " -> File already exists" << std::endl;
            return false;
            break;

        case UnknownIssue:
            client.packet << ServerFailure;
            client.socket.send(client.packet);
            tprint();
            std::cout << client.name() << " -> Couldn't create file" << std::endl;
            return false;
            break;

        default:
            break;
    }

    std::ofstream output_file ( client.path.c_str(), std::ios::binary | std::ios::out );

    unsigned int loop_number(filesize/bytes_per_packet);
    char* input_data_array = new char[bytes_per_packet];
    sf::Int8 input_data;
    unsigned char percentage_count(0);

    client.packet << ServerReady;
    client.socket.send(client.packet);
    client.packet.clear();

    tprint();
    setColors("light blue");
    std::cout << "* Start downloading " << client.path << " from " << client.name() << std::endl;
    setColors("reset");
    
    for( unsigned int i(0) ; i<loop_number ; ++i){

        if(client.socket.receive( client.packet ) == sf::Socket::Disconnected){
            tprint();
            std::cout << client.name() << " - ";
            setColors("light red");
            std::cout << "connection lost" << std::endl;
            setColors("reset");
            output_file.close();
            removeFile(client.path);
            return false;
        }

        for( unsigned int j(0) ; j<bytes_per_packet ; ++j ){
            client.packet >> input_data;
            input_data_array[j]=static_cast<char>(input_data);
        }

        output_file.write( input_data_array, bytes_per_packet );
        client.packet.clear();

        if( static_cast<unsigned char>(100*i/loop_number) > percentage_count ){
            tprint();
            std::cout << client.name() << " - ";
            setColors("light blue");
            std::cout << "[" << static_cast<short>(percentage_count) << "%]";
            setColors("reset");
            std::cout << " of download" << std::endl;
            percentage_count = static_cast<unsigned char>(percentage_count + 25);
        }
    }

    filesize -= loop_number * bytes_per_packet;
    if( filesize > 0 ){

        if(client.socket.receive( client.packet ) == sf::Socket::Disconnected){
            tprint();
            std::cout << client.name() << " - ";
            setColors("light red");
            std::cout << "connection lost" << std::endl;
            setColors("reset");
            output_file.close();
            removeFile(client.path);
            return false;
        }

        for( unsigned int j(0) ; j < client.packet.getDataSize() ; ++j){
            client.packet >> input_data;
            output_file << static_cast<char>(input_data);
        }
    }

    output_file.close();

    tprint();
    std::cout << client.name() << " - ";
    setColors("light blue");
    std::cout << "[100%]";
    setColors("reset");
    std::cout << " Transfer terminated successfully" << std::endl;
    createInformationFile(client);
    delete[] input_data_array;
    return true;
}
