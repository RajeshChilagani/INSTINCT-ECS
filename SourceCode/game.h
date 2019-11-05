/*game.h is the game header file.In game.h Game class is defined with member methods and member variables declared.Game class holds entire game logic*/
#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<fstream>
#include<vector>
#include "Vector2D.h"
class ColliderComponent;
using namespace std;

class Game 
{
private:
	bool isRunning;
	SDL_Window *window;
	int count=0;
	int counter;
	SDL_Texture* gameInfo;
	SDL_Rect gameInfosrc, gameInfodes;
	int level = 0;
	int score;
	int highScore;
	int gameHeight, gameWidth, border;
	int counterValue;
	float projectileSpeed;
public :
	static bool isPlayerDead;
	static bool gamesOnPause;
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static vector<ColliderComponent*> colliders;
	Game();
	~Game();
	void init(const char* title,int xpos,int ypos,int width,int height,bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool runing() { return isRunning; }
	void createProjectiles(float x, float y, int tagID,Vector2D vec);
	void random(Vector2D vec);
	void otherActions();
	void levels();
};