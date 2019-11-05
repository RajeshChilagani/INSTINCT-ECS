/*In Map.h header file Map class is defined with members(variables and methods) declared*/
#pragma once
#include "game.h"

class Map
{
private:
	SDL_Rect srcRect, desRect;
	SDL_Texture* texture1;
	SDL_Texture* texture2;
	SDL_Texture* texture3;
	SDL_Texture* texture4;
	int** mapArray;
	int rowCount, colCount;
public:
	Map(const char* filePath,int width,int height);
	~Map();

	void loadMap(vector<int> myVector);
	void drawMap();
	void clearArray();
};
