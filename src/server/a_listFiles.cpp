#include "s_a_listFiles.hpp"

bool a_listFiles(Client& client, Config* config){
    
    //checking allowance and sending what's up about this
    
    DIR* directory = opendir(client.path.c_str());
    struct dirent* redfile = NULL;
    client.packet.clear();

    std::cout << "\t-Directory: " << client.path << std::endl;

    if( directory == NULL ){
        client.packet << VoidDirectory;
        client.socket.send( client.packet );
        tprint();
        std::cout << client.name() << " -> Could not open the directory" << std::endl;
        return false;
    }//else
    
    client.packet << ServerReady;
    client.socket.send( client.packet );
    tprint();
    std::cout << client.name() << " -> Server ready to list" << std::endl;

    client.packet.clear();

    if(client.path == "./Public/" 
    && (config->privateFolderReadingAllowed() || config->privateFolderWritingAllowed())){
        client.packet << 14 
        << static_cast<sf::Int32>(':')
        << static_cast<sf::Int32>('P')
        << static_cast<sf::Int32>('r')
        << static_cast<sf::Int32>('i')
        << static_cast<sf::Int32>('v')
        << static_cast<sf::Int32>('a')
        << static_cast<sf::Int32>('t')
        << static_cast<sf::Int32>('e')
        << static_cast<sf::Int32>('/')
        << static_cast<sf::Int32>(' ')
        << static_cast<sf::Int32>(':')
        << static_cast<sf::Int32>(' ')
        << static_cast<sf::Int32>(':')
        << static_cast<sf::Int32>(' ');
        client.socket.send( client.packet );
    }

    while( (redfile = readdir( directory )) != NULL ){

        std::string tmp( redfile->d_name );
        std::string info_path = "./FilesData" + client.path.substr(1, std::string::npos); //add "./FilesData" at the begening
        info_path += tmp; //add the filename at the end
        info_path = info_path.insert(info_path.find_last_of("/") + 1,"."); //insert '.' before the filename
        std::string info_date = " ";
        std::string info_user = " ";

        if( isFolder(client.path + tmp) ){
            tmp = ":" + tmp + "/";
        }

        if (tmp != ":../" && tmp != ":./"){
            
            std::ifstream file (info_path.c_str(), std::ios::binary | std::ios::in );

            if( file.fail() ){
                
                file.close();
                std::cout << "\t-File: " << info_path << std::endl;
                std::cout << "\t-";
                setColors("light red");
                std::cout << "Error reading the file" << std::endl;
                setColors("reset");
            }
            else{

                bool filename_printed(false);
            std::getline( file, info_date );

                if( file.fail() ){

                    std::cout << "\t-File: " << info_path << std::endl;
                    filename_printed = true;
                    std::cout << "\t-";
                    setColors("light yellow");
                    std::cout << "Error reading the date" << std::endl;
                    setColors("reset");
                }
                info_date = info_date.substr(0,12); //just keep the day

            std::getline(file, info_user);
                if( file.fail() ){
                    
                    if(!filename_printed)
                        std::cout << "\t-File: " << info_path << std::endl;

                    std::cout << "\t-";
                    setColors("light yellow");
                    std::cout << "Error reading the username" << std::endl;
                    setColors("reset");
                }
                file.close();
            }
        }

        tmp = tmp + ":" + info_date + ":" + info_user;
        
        client.packet.clear();
        client.packet << static_cast<unsigned int>( tmp.length() );

        for( unsigned short i(0) ; i < tmp.length() ; ++i ){
            client.packet << static_cast<sf::Int32>( tmp[i] );
        }

        client.socket.send( client.packet );

    }

    client.packet.clear();
    client.packet << 0 << EndOfStream;
    client.socket.send( client.packet );
    tprint();
    std::cout << client.name() << " -> file listed" << std::endl;

    return true;
}
