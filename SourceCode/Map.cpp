/*In Map.cpp,methods declared in Map class are defined
Map class loads maps from files.*/
#include "Map.h"
#include "TextureManager.h"
#include "File.h"
Map::Map(const char* filePath,int width,int height)
{
	texture1 = TextureManager::loadTexture("assets/level1.png");
	texture2 = TextureManager::loadTexture("assets/level2.png");
	texture3 = TextureManager::loadTexture("assets/level3.png");
	texture4 = TextureManager::loadTexture("assets/level4.png");
	colCount = int(width / 32);
	rowCount = int(height/32);
	rowCount = rowCount + 1;
	mapArray = new int* [rowCount];
	for (int i = 0; i < rowCount; i++)
	{
		mapArray[i] = new int[colCount];
	}
	fstream mapFile = File::fileOpen(filePath);
	vector<int> myVector = File::loadMap(mapFile);
	File::closeFile(mapFile);
	loadMap(myVector);
	cout << " vect" << myVector.capacity();
	File::clearVector(myVector);
	srcRect.x = srcRect.y = 0;
	srcRect.h = desRect.h = 32;
	srcRect.w = desRect.w=32;
	desRect.x = desRect.y = 0;
}
Map::~Map()
{
	SDL_DestroyTexture(texture1);
	SDL_DestroyTexture(texture2);
	SDL_DestroyTexture(texture3);
}
void Map::loadMap(vector<int> myVector)
{
	//Data from vector is loaded into dynamic array created before.
	int z = 0;
	for (int row = 0; row < rowCount; row++)
	{
		for (int col = 0; col < colCount; col++)
		{
			mapArray[row][col] = myVector[z];
			z++;
		}
	}
}
void Map::drawMap()
{
	int type=0;
	for (int row = 0; row < rowCount; row++)
	{
		for (int col = 0; col < colCount; col++)
		{
			type = mapArray[row][col];
			desRect.x = col * 32;
			desRect.y = row * 32;
			//desRect.w = srcRect.w * 2;
			//desRect.h = srcRect.h * 2;
			switch (type)
			{
			case 0:
				TextureManager::draw(texture1,srcRect,desRect);
				break;
			case 1:
				TextureManager::draw(texture2, srcRect, desRect);
				break;
			case 2:
				TextureManager::draw(texture3, srcRect, desRect);
				break;
			case 3:
				TextureManager::draw(texture4, srcRect, desRect);
				break;
			default:
				break;
			}
		}
	}
}
void Map::clearArray()
{
	for (int i = 0; i < rowCount; i++)
	{
		delete[] mapArray[i];
	}
	delete mapArray;
}
