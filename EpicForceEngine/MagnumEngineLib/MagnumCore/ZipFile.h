#ifndef _ZipFile_h_
#define _ZipFile_h_

#include "Array.h"
#include "EString.h"
using namespace Magnum;

namespace Magnum
{

class ZipFile
{
public:
	ZipFile();
	~ZipFile();

	bool open(const char *zipPath);
	void close();

	int getNumFiles() const;
	bool isFileExists(const char *filePath) const;
	void getFilesList(Vector<String> &filePaths) const;

	bool extractFile(const char *filePath) const;
	bool extractAllFiles(const char *destPath) const;
private:
	void *handle;
};

};

#endif