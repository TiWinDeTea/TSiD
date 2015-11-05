#include "s_Config.hpp"

Config::Config( bool rights[2] )
{
	user_creation_allowed = rights[0];
	private_folder_usage_allowed = rights[1];
}
