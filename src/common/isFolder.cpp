#include "../../include/common/isFolder.hpp"

bool isFolder(std::string const& path)
{

#ifdef OS_WINDOWS
    return (!fileExist(path));
#else
	struct stat s;
	if( stat( path.c_str() ,&s ) == 0 )
		return (s.st_mode & S_IFDIR);
	else
		return false;
#endif
}
