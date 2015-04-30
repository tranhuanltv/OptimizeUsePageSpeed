#pragma once
#include <string>
class DirectoryTool
{
public:
	static bool createDir(const std::string& dir_name);
	static void createDirTree(const std::string& full_path);
private:
	DirectoryTool(void);
	~DirectoryTool(void);
};
