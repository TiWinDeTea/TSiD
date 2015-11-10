#ifndef S_CLIENT_HPP_INCLUDED
#define S_CLIENT_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include "SCommand.hpp"
#include "s_tprint.hpp"

class Client {

 public:
    /**
     * @brief Default constuctor
     */
    Client();

    /**
     * @brief Default destructor
     */
    ~Client(){};

    /**
     * @brief Wait for a new client
     * @details Timeout: 60sec, if a new client is found call connectUser()
     * 
     * @param listener Pointer on a listener listening on the server port
     * @return true if a client is now connected
     * false if no client try to connect or if they fail
     */
    bool getNewClient(sf::TcpListener *listener);

    /**
     * @brief Disconnect a client
     * @details put state variable to false
     */
    void disconnect();

    /**
     * @brief Return the state of the client
     * @return true if the client is connected,
     * false if he is diconnected
     */
    bool isConnected();

    /**
     * @brief *
     * @return true if the path is in /Private,
     * false else
     */
    bool isInPrivate();

    /**
     * @brief Return the client username
     * @return user_name
     */
    std::string name() const;

    // dirty little code
    sf::Packet packet;
    sf::TcpSocket socket;
    std::string path;

 private:

    std::string user_name;
    bool state;

    /**
     * @brief Connect a new client
     * @details Verify the username and password before connection
     * @return true if the client is connected,
     * false if he is diconnected
     */
    bool connectUser();
};

#endif
