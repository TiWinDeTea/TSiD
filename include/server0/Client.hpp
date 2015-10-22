#ifndef CLIENT_HPP_INCLUDED
#define CLIENT_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include "../common/SCommand.hpp"

class Client {

 public:

    Client(){ user_name=""; };
    ~Client(){};
    bool getNewClient(unsigned short port);
    void disconnect();
    std::string name() const;

    // dirty little code
    sf::Packet packet;
    sf::TcpSocket socket;

 private:

    std::string user_name;
    bool connectUser();
};

#endif
