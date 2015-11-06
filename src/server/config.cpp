#include "s_Config.hpp"

Config::Config( bool rights[CONFIG_SIZE] )
{
	user_creation_allowed = rights[0];
	private_folder_reading_allowed = rights[1];
	private_folder_writing_allowed = rights[2];
}
