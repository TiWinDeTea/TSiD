#ifndef S_CONFIG_HPP_INCLUDED
#define S_CONFIG_HPP_INCLUDED

#define CONFIG_SIZE 3
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
	Config(	bool rights[CONFIG_SIZE] );

	/**
	 * returns the value of user_creation_allowed
	 * @return true if the creation of a new user is allowed
	 */
	bool userCreationAllowed(){ return user_creation_allowed; }

	/**
	 * returns the value of private_folder_reading_allowed
	 * @return true if users may write and read in their private folders
	 */
	bool privateFolderReadingAllowed(){ return private_folder_reading_allowed; };

	/**
	 * returns the value of
	 * @return true if users may write in their private folders private_folder_writing_allowed
	 */
	bool privateFolderWritingAllowed(){ return private_folder_writing_allowed; };

private:

	bool user_creation_allowed,
		 private_folder_reading_allowed,
		 private_folder_writing_allowed;
};

#endif
