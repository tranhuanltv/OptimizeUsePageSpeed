#include <stdlib.h> // system
#include "DirectoryTool.h"
#include "FileUtil.h"
#include "StringUtil.h"

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

void optimize(int type, const char* input_dir, const char *out_dir) 
{
	std::vector<std::string> files;
    std::vector<std::string> folders;
    
	ListFilesInFolder(kTypeInfo[type].extension, input_dir, &files, &folders);

    if (files.empty()) return;
    
    // Create output directories for store result files
    if (!DirectoryTool::createDirs(folders, input_dir, out_dir))
        return;
	
    std::vector<std::string>::iterator iter = files.begin();
    for ( ; iter != files.end(); ++iter)
    {
        const char * optimizeTool = kTypeInfo[type].execution;
        
        string outFile = StringUtil::replace(*iter, input_dir, out_dir);
        
        std::string input_indicate;
        std::string output_indicate;
        
        if (type == 2 || type == 3)
        {
            input_indicate = "-input_file ";
            output_indicate = "-output_file ";
        }
        
        std::string cssCommand = string(optimizeTool)
            + SPACECHAR
            + input_indicate
            + quote(*iter)
            + SPACECHAR
            + output_indicate
            + quote(outFile);
        
        int ret = system(cssCommand.c_str());
        printf("%d  %s\n", ret, cssCommand.c_str());
    }
    
}


int main(int argc, char** argv)
{
	if (argc < 3)
	{
		PrintUsage();
		return EXIT_FAILURE;
	}

	const char* input_dir = argv[1];
	const char* output_dir = argv[2];

	DirectoryTool::createDir(output_dir);
	for (int i = 0; i < sizeof(kTypeInfo)/ sizeof(ScanInfo); ++i)
		optimize(i, input_dir, output_dir);
    
    return EXIT_SUCCESS;
}