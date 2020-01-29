#pragma once

#include <iostream>

#include <string>

using namespace std;

class FileIo {	

private:
	//FileIo();
	//~FileIo();

	string root_file_path;

	string file_path;

	

public:

	FileIo();

	void SetRootFilePath();

	string GetRootFilePath(void);

	void SetFilePath(string file_path);

	string GetFilePath(void);
};