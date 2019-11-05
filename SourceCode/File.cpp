/*In File.cpp methods declared in File class are defined*/
#include "File.h"
fstream File::fileOpen(const char* filepath)
{
	fstream file;
	file.open(filepath);
	return file;
	
}
vector<int> File::loadMap(fstream& file)
{
	vector<int> myVector;
	while (!file.eof())
	{
		int x;
		file >> x;
		myVector.push_back(x);
	}
	return myVector;
}
void File::closeFile(fstream& file)
{
	file.close();
}
void File::clearVector(vector<int> myVector)
{
	myVector.clear();
}