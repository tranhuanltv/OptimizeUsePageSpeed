#include <stdlib.h> // system
#include "DirectoryTool.h"
#include "FileUtil.h"

#define SPACECHAR ' '
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

void PrintUsage()
{
	printf("Usage: app input_dir output_dir\n");
}

std::string quote(const std::string &val)
{
	return "\"" + val + "\"";
}


struct ScanInfo
{
	char *extension;
	char *execution;
};

//const int NUMBER_FILE_TYPE = 2;
ScanInfo kTypeInfo[] =
{ 
	{"css", "./minify_css_bin"},
	{"js", "./minify_js_bin"},
    {"png", "./optimize_image_bin"},
    {"jpg", "./optimize_image_bin"}
};

std::string replace(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return str;
    str.replace(start_pos, from.length(), to);
    return str;
}

void optimize(int type, const char* input_dir, const char *out_dir) 
{
	std::vector<std::string> cssFiles;
	ListFilesInFolder(kTypeInfo[type].extension, input_dir, &cssFiles);
    
    std::sort(cssFiles.begin(), cssFiles.end());

	if (!cssFiles.empty())
	{
		for (int i = 0; i < cssFiles.size(); ++i)
		{
			const char * optimizeCssTool = kTypeInfo[type].execution;
            
            string outFile = replace(cssFiles.at(i), input_dir, out_dir);
            
            std::string input_indicate;
            std::string output_indicate;
            
            if (type == 2 || type == 3)
            {
                input_indicate = "-input_file ";
                output_indicate = "-output_file ";
            }
            
			std::string cssCommand = string(optimizeCssTool)
				+ SPACECHAR
                + input_indicate
				+ quote(cssFiles.at(i)) 
				+ SPACECHAR
                + output_indicate
				+ quote(outFile);
            
            if (!DirectoryTool::createDir(GetFilePath(outFile)))
            {
                DirectoryTool::createDirTree(GetFilePath(outFile));
            }
			
			int ret = system(cssCommand.c_str());
			printf("%d  %s\n", ret, cssCommand.c_str());
		}
	}
}


int main(int argc, char** argv) 
{
	if (argc < 3)
	{
		PrintUsage();
		return EXIT_FAILURE;
	}

	const char *input_dir = argv[1];
	const char *output_dir = argv[2];

	DirectoryTool::createDir(output_dir);
	for (int i = 0; i < sizeof(kTypeInfo)/ sizeof(ScanInfo); ++i)
		optimize(i, input_dir, output_dir);

}