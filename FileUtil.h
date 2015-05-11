#include <string>
#include <vector>

#if !defined(_WIN32)
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#define SLASH_STRING '/'
#else
#include <Windows.h>
#include "dirent.h"
#define SLASH_STRING '\\'
#endif

using std::string;
using std::vector;

void ListFilesInFolder(const string& fileExtension
                       , const string& folderPath
                       , vector<string>* vFileNames
                       , vector<string>* vFolderStructures)
{
	DIR *dir = opendir(folderPath.c_str());
	if(0 == dir)
    {
        printf("Cannot access %s\n", folderPath.c_str());
        return;
    }
    
    vFolderStructures->push_back(folderPath);
    
    //printf("Folder path: %s\n", folderPath.c_str());
    
    dirent *entry;
    while((entry = readdir(dir)) != 0)
    {
        
        string fileName(entry->d_name);
        
        if (fileName == ".." || fileName == ".")
            continue;
        
        string fullPath = folderPath + SLASH_STRING + fileName;

#ifdef _WIN32
		if (entry->data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
#else
        if (entry->d_type == DT_DIR)
#endif
        {
            ListFilesInFolder(fileExtension, fullPath, vFileNames, vFolderStructures);
            continue;
        }
        
        string dotExtension = "." + fileExtension;
        size_t extPosition = fileName.rfind(dotExtension);
        if (extPosition != string::npos)
        {
            string extString = fileName.substr(extPosition);
            if (extString == dotExtension)
            {
                vFileNames->push_back(fullPath);
            }
        }
    }
    closedir(dir);
}

bool WriteBin(const string& fileName, const void* src, size_t srcLen)
{
	FILE* pf = fopen(fileName.c_str(), "wb");
	if (pf)
	{
		size_t byteWritten = fwrite(src, 1, srcLen, pf);
		fclose(pf);
		return (byteWritten == srcLen);
	}
	return false;
}

string RemoveFileExtension(const string& fullFileName)
{
	size_t lastPos = fullFileName.rfind(".");
	if (lastPos != string::npos)
	{
		return fullFileName.substr(0, lastPos);
	}
	else
	{
		return fullFileName;
	}
}

string GetFileName(const string& filePath)
{
	size_t lastPos = filePath.rfind(SLASH_STRING);
	if (lastPos != string::npos)
	{
		return filePath.substr(lastPos+1);
	}
	else
	{
		return filePath;
	}
}

string GetFilePath(const string& fullFilePath)
{
    size_t lastPos = fullFilePath.rfind(SLASH_STRING);
    if (lastPos != string::npos)
    {
        return fullFilePath.substr(0, lastPos);
    }
    else
    {
        return fullFilePath;
    }
}