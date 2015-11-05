#ifndef S_CONFIG_HPP_INCLUDED
#define S_CONFIG_HPP_INCLUDED

/**
 * @class This class is to contain the server's configuration. It's a read-only class
 */
class Config{

public:

	/**
	 * Client constructor; Sets the variables
	 * @param user_creation_allowed        Sets the authorization for the creation of new users
	 * @param private_folder_usage_allowed Sets the authorization for using the Private folder
	 */
	Config(	bool rights[2] );

	/**
	 * returns the value of
	 * @return true if the creation of a new user is allowed
	 */
	bool userCreationAllowed(){ return user_creation_allowed; }

	/**
	 * returns the value of
	 * @return true if users may use their private folders
	 */
	bool privateFolderUsageAllowed(){ return private_folder_usage_allowed; };

private:

	bool user_creation_allowed,
	     private_folder_usage_allowed;
};

#endif
