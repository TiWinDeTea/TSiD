#include "s_a_download.hpp"

bool a_retrieveData(Client& client){

    unsigned int file_size;
    unsigned int bytes_per_packet;

    if( !(client.packet >> file_size >> bytes_per_packet) ){
        client.packet.clear();
        client.packet << UnknownIssue;
        client.socket.send(client.packet);
        tprint();
        std::cout << client.name() << " -> There was an error reading file infos" << std::endl;
        return false;
    }
    std::cout << "\t-File: " << client.path << std::endl;

    if( file_size == 0 ){
        client.packet.clear();
        client.packet << UnknownIssue;
        client.socket.send( client.packet );
        tprint();
        std::cout << client.name() << " -> Could not read file size" << std::endl;
        return false;
    }

    if(file_size < 1024 ){
        std::cout << "\t-File size: " << file_size << " B" << std::endl;
    }
    
    else if(file_size < 1024 * 1024 ){
        std::cout << "\t-File size: " << file_size/1024 << " KiB" << std::endl;
    }
    
    else if(file_size < 1024 * 1024 * 1024 ){
        std::cout << "\t-File size: " << file_size/(1024 * 1024)<< " MiB" << std::endl;
    }
    
    else{
        std::cout << "\t-File size: " << file_size/(1024 * 1024 * 1024)<< " GiB" << std::endl;
    }

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

    unsigned int loop_number(file_size/bytes_per_packet);
    char* input_data_array = new char[bytes_per_packet];
    sf::Int8 input_data;
    unsigned char percentage_count(0);

    client.packet.clear();
    client.packet << ServerReady;
    client.socket.send(client.packet);

    tprint();
    setColors("light blue");
    std::cout << "* Start downloading " << client.path << " from " << client.name() << std::endl;
    setColors("reset");
    
    for( unsigned int i(0) ; i<loop_number ; ++i){
        
        client.packet.clear();

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

    file_size -= loop_number * bytes_per_packet;
    if( file_size > 0 ){
        
        client.packet.clear();
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
    createInformationFile(client.path, client.name());
    delete[] input_data_array;
    return true;
}
