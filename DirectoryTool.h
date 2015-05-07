#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

class DirectoryTool
{
public:
	static bool createDir(const string& dir_name);
    static bool createDirs(const vector<string>& dirs, const string& fromDir, const string& toDir);
	static void createDirTree(const string& full_path);
private:
	DirectoryTool(void);
	~DirectoryTool(void);
};
