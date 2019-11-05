/*In File.h header file File class is defined with members declared to open and close files*/
#pragma once
#include "game.h"
class File
{
private:
public:
	static fstream fileOpen(const char* filepath);
	static vector<int> loadMap(fstream& file);
	static void closeFile(fstream& file);
	static void clearVector(vector<int> myVector);

};
