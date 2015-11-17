#include "s_a_changePassword.hpp"

bool a_changePassword(Client& client){

	std::string old_password, new_password;

	if( !(client.packet >> old_password >> new_password) ){
        client.packet.clear();
        client.packet << UnknownIssue;
        client.socket.send(client.packet);
        tprint();
        std::cout << client.name() << " -> There was an error reading new password" << std::endl;
        return false;
    }

    std::ifstream i_user_file( ("UsersData/" + client.name()).c_str(), std::ios::in);
	if( i_user_file.fail() ){

		i_user_file.close();
		std::cout << "\t-File: " << "UsersData/" + client.name() << std::endl;
        std::cout << "\t-";
        setColors("light red");
        std::cout << "Error reading the file" << std::endl;
        setColors("reset");

		client.packet.clear();
        client.packet << UnknownIssue;
        client.socket.send(client.packet);
        tprint();
        std::cout << client.name() << " -> There was an error reading user file" << std::endl;
		return false;
	}

	std::string actual_password;
	std::getline(i_user_file, actual_password);
	i_user_file.close();

	if(actual_password != old_password){

		client.packet.clear();
        client.packet << BadID;
        client.socket.send(client.packet);
        tprint();
        std::cout << client.name() << " -> ";
        setColors("light yellow");
        std::cout << "wrong password" << std::endl;
        setColors("reset");
		return false;
	}

	std::ofstream o_user_file( ("UsersData/" + client.name()).c_str(), std::ios::out | std::ios::trunc );
	if( o_user_file.fail() ){

		o_user_file.close();
		std::cout << "\t-File: " << "UsersData/" + client.name() << std::endl;
        std::cout << "\t-";
        setColors("light red");
        std::cout << "Error reading the file" << std::endl;
        setColors("reset");

		client.packet.clear();
        client.packet << UnknownIssue;
        client.socket.send(client.packet);
        tprint();
        std::cout << client.name() << " -> There was an error reading user file" << std::endl;
		return false;
	}

	o_user_file << new_password;
	o_user_file.close();

	client.packet.clear();
    client.packet << Success;
    client.socket.send(client.packet);
    return true;
}