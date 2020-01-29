
#include "FileIo.h"

FileIo::FileIo(){
	root_file_path = "C:\\Users\\masaki\\Pictures\\image";
};




void FileIo::SetRootFilePath() {
	root_file_path = "C:\\Users\\masaki\\Pictures\\image";
}

string FileIo::GetRootFilePath(void) {
	return root_file_path;
}


// ƒtƒ@ƒCƒ‹‚ð“Ç‚Ýž‚Þ
void FileIo::SetFilePath(string file_path) {
	this->file_path = file_path;
}

string FileIo::GetFilePath(void) {
	return file_path;
}