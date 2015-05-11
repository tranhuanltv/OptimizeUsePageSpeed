#include "DirectoryTool.h"
#include "StringUtil.h"

#ifdef _WIN32
#include <Windows.h>
#define SLASH_CHAR '\\'
#else
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#define SLASH_CHAR '/'
#endif // _WIN32

DirectoryTool::DirectoryTool(void)
{
}

DirectoryTool::~DirectoryTool(void)
{
}

bool DirectoryTool::createDir(const string& dir_name)
{
#ifdef _WIN32
	bool ret = CreateDirectoryA(dir_name.c_str(), NULL);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		return true;
	return ret;
#else
    //printf("Create dir: %s\n", dir_name.c_str());
	int ret = mkdir(dir_name.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
    if (errno == EEXIST)
        return true;
    
    return ret == 0;
#endif // _WIN32
}

bool DirectoryTool::createDirs(const vector<string>& dirs, const string& fromDir, const string& toDir)
{
    for (int i = 0; i < dirs.size(); ++i)
    {
        string dir = StringUtil::replace(dirs.at(i), fromDir, toDir);
        if (!createDir(dir))
		{
			printf("Failed create: %s\n", dir.c_str());
            return false;
		}
    }
    
    return true;
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
