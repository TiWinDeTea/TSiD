#ifndef CLIENT_HPP_INCLUDED
#define CLIENT_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include "../common/SCommand.hpp"
#include "tprint.hpp"

class Client {

 public:

    Client(){ user_name=""; state=false; };
    ~Client(){};
    bool getNewClient(sf::TcpListener *listener);
    void disconnect();
    bool isConnected();
    std::string name() const;

    // dirty little code
    sf::Packet packet;
    sf::TcpSocket socket;
    std::string path;

 private:

    std::string user_name;
    bool state;
    bool connectUser();
};

#endif
