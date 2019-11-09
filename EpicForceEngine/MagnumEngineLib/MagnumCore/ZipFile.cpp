#include "ZipFile.h"
#include "unzip.h"

ZipFile::ZipFile()
: handle(0)
{
}

ZipFile::~ZipFile()
{
}

bool ZipFile::open(const char *zipPath)
{
	handle = unzOpen(zipPath);

	return handle!=0;
}

void ZipFile::close()
{
	assert(handle);

	unzClose(handle);
}

int ZipFile::getNumFiles() const
{
	assert(handle);

	unz_global_info info;
	unzGetGlobalInfo(handle, &info);

	return info.number_entry;
}

bool ZipFile::isFileExists(const char *filePath) const
{
	return unzLocateFile(handle, filePath, 0)!=UNZ_END_OF_LIST_OF_FILE;
}

void ZipFile::getFilesList(Vector<String> &filePaths) const
{
	char fileName[4096];
	int rval = unzGoToFirstFile(handle);

	while(rval!=UNZ_END_OF_LIST_OF_FILE)
	{
		unz_file_info fileInfo;
		unzGetCurrentFileInfo(handle,
							  &fileInfo,
							  fileName,
							  4096,
							  0,
							  0,
							  0,
							  0);
		
		filePaths.push() = fileName;

		rval = unzGoToNextFile(handle);
	};
}

bool ZipFile::extractFile(const char *filePath) const
{
	return 0;
}

bool ZipFile::extractAllFiles(const char *destPath) const
{
	return 0;
}