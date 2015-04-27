#include "DirectoryTool.h"

#ifdef _WIN32
#include <Windows.h>
#define SLASH_CHAR '\\'
#else
#include <sys/stat.h>
#include <sys/types.h>
#define SLASH_CHAR '/'
#endif // _WIN32

DirectoryTool::DirectoryTool(void)
{
}

DirectoryTool::~DirectoryTool(void)
{
}

void DirectoryTool::createDir( const std::string& dir_name )
{
#ifdef _WIN32
	CreateDirectoryA(dir_name.c_str(), NULL);
#else
	mkdir(dir_name.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
#endif // _WIN32
}

void DirectoryTool::createDirTree( const std::string& full_path )
{
	size_t pos = 0;
	while(pos != std::string::npos)
	{
		pos = full_path.find(SLASH_CHAR, pos + 1);
		createDir(full_path.substr(0, pos));
	}
}
