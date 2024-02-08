#pragma once

#include <string>
#include <fstream>
#include <cstdio>

class FileDeleter
{
	std::string filename;
public:
	FileDeleter (const std::string&fn):filename(fn){}
	void operator ()(std::ofstream* fp)
	{
		fp->close();
		std::remove(filename.c_str());
		delete fp;
	}
};

template<typename T>
class UniqCountDeleter
{
	size_t n;
public:
	size_t GetN()const { return n; }
	UniqCountDeleter(size_t n):n(n){}
	void operator()(T* p) { delete[] p; }
};

