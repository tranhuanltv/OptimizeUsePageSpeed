#include "DirectoryTool.h"
#include "FileUtil.h"
#include <process.h>

#define SPACECHAR ' '

void PrintUsage()
{
	printf("Usage: app input_dir output_dir");
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

const int NUMBER_FILE_TYPE = 2;
ScanInfo kTypeInfo[NUMBER_FILE_TYPE] = 
{ 
	{"css", "minify_css_bin"},
	{"js", "minify_js_bin"},
};

void optimize(int type, const char* input_dir, const char *out_dir) 
{
	std::vector<std::string> cssFiles;
	ListFilesInFolder(kTypeInfo[type].extension, input_dir, &cssFiles);

	if (!cssFiles.empty())
	{
		for (int i = 0; i < cssFiles.size(); ++i)
		{
			const char * optimizeCssTool = kTypeInfo[type].execution;
			std::string cssCommand = string(optimizeCssTool)
				+ SPACECHAR 
				+ quote(cssFiles.at(i)) 
				+ SPACECHAR
				+ quote(string(out_dir) + SLASH_STRING + GetFileName(cssFiles.at(i)));
			
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

	DirectoryTool::createDirTree(output_dir);
	for (int i = 0; i < sizeof(kTypeInfo)/ sizeof(ScanInfo); ++i)
		optimize(i, input_dir, output_dir);

}