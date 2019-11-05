/*In game.cpp all methods declared in Game class are defined and variables are initialized*/
#include "game.h"
#include "TextureManager.h"					  
#include "Map.h"							  
#include "Collision.h"						  
#include "EntityComponentSystem/Components.h" 
#include <string>
Manager manager;
Map* areaMap;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::isPlayerDead = false;
bool Game::gamesOnPause = true;
vector<ColliderComponent*>Game::colliders;
auto& player(manager.addEntity());
auto& leftWall(manager.addEntity());
auto& rightWall(manager.addEntity());
auto& topWall(manager.addEntity());
auto& bottomWall(manager.addEntity());
auto& UIobject(manager.addEntity());

Game::Game()
{}
Game::~Game()
{}
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) 
{
	//init() method initializes all entities and variables required.
	gameHeight = height;     
	gameWidth = width;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		int flags = 0;
		if (fullscreen)
		{
			flags = SDL_WINDOW_FULLSCREEN;
		}
		cout << "SubSystems initialised" << endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			//cout << "renderer is created" << endl;
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
	score = 0;
	highScore = score;
	levels();
	int bor = 5;
	border = bor;
	leftWall.addComponent<TileComponent>(0, 0, border, gameHeight, 1);
	leftWall.addComponent<ColliderComponent>("Boundary");
	rightWall.addComponent<TileComponent>(gameWidth - border, 0, border, gameHeight, 1);
	rightWall.addComponent<ColliderComponent>("Boundary");
	topWall.addComponent<TileComponent>(border, 0, gameWidth - border + border, border, 1);
	topWall.addComponent<ColliderComponent>("Boundary");
	bottomWall.addComponent<TileComponent>(border, gameHeight - border, gameWidth - border + border, border, 1);
	bottomWall.addComponent<ColliderComponent>("Boundary");

	player.addComponent<TransformComponent>(640.0, 360.0, 1, 64, 64);
	player.addComponent<SpriteComponent>("assets/playerSprite.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");


	if (TTF_Init() == -1)
	{
		cout << "Error:SDL_TTF" << endl;
	}
	SDL_Color white = { 255,255,255,255 };
	UIobject.addComponent<UILabel>("assets/Games.ttf", white, 16);
	UIobject.getComponent<UILabel>().addLabel(15, 15, "Score. " + to_string(score));
	UIobject.getComponent<UILabel>().addLabel(15, 35, "HighScore. " + to_string(highScore));

	gameInfosrc.x = 0;
	gameInfosrc.y = 0;
	gameInfodes.x = int(gameWidth / 2) - 256;
	gameInfodes.y = int(gameHeight / 2) - 256;
	gameInfosrc.h = gameInfosrc.w = 256;
	gameInfodes.h = gameInfodes.w = 512;


}

void Game::handleEvents()
{
	//handleEvents method handles all game events like keyboard actions and etc (ex:keydowns).
	SDL_PollEvent(&event);
	switch (event.type)
	{

	case SDL_QUIT:
		isRunning = false;
		break;
	}
	if (event.type == SDL_KEYDOWN)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			isRunning = false;
			break;
		case SDLK_p:
			gamesOnPause = true;
			break;
		case SDLK_c:
			gamesOnPause = false;
			break;
		case SDLK_r:
			if (isPlayerDead && !gamesOnPause)
			{
				isPlayerDead = false;
				score = 0;
				player.getComponent<SpriteComponent>().play("idle");
				counter = 100;
				player.getComponent<TransformComponent>().scale = 1;
			}

			break;
		default:
			break;
		}
	}
}
void Game::update() 
{
	//update() method updates all entities,their components and game logic.
	if (!gamesOnPause)
	{
		
		if (!isPlayerDead)
		{
			if (counter == counterValue)
			{
				float x =projectileSpeed, y =projectileSpeed;
				random(Vector2D(x, y));
				random(Vector2D(-x, y));
				random(Vector2D(x, -y));
				random(Vector2D(-x, -y));
			}
			counter++;
		}


		manager.refresh();
		manager.update();

		for (auto cc : colliders)
		{

			if (cc->tag == "Boundary")
			{
				if (!isPlayerDead)
				{
					if (Collision::AABB(player.getComponent<ColliderComponent>(), *cc))
					{
						player.getComponent<TransformComponent>().velocity *-1;
						if (score > 0)
						score--;

					}
				}
				

			}
			if (cc->tag == "projectile")
			{

				if (!isPlayerDead)
				{
					if (Collision::AABB(player.getComponent<ColliderComponent>(), *cc))
					{
						if (cc->entity->getComponent<ProjectileComponent>().tagName == "increase")
						{
							if (player.getComponent<TransformComponent>().scale < 3 && player.getComponent<TransformComponent>().scale > 0)
							{
								player.getComponent<TransformComponent>().scale++;

							}
							else
							{
								if (!isPlayerDead)
								{
									if (score > 0)
										score--;
								}

							}

						}
						else if (cc->entity->getComponent<ProjectileComponent>().tagName == "decrease")
						{
							if (player.getComponent<TransformComponent>().scale <= 3 && player.getComponent<TransformComponent>().scale > 1)
							{
								player.getComponent<TransformComponent>().scale--;

							}
							else
							{
								if (!isPlayerDead)
								{
									score++;
								}

							}

						}
						else if (cc->entity->getComponent<ProjectileComponent>().tagName == "kill")
						{
							player.getComponent<SpriteComponent>().play("dead");
							level = 0;
							isPlayerDead = true;
							player.getComponent<TransformComponent>().velocity.x = 0;
							player.getComponent<TransformComponent>().velocity.y = 0;
						}



						cc->entity->destroy();
					}
				}

				if (Collision::AABB(leftWall.getComponent<ColliderComponent>(), *cc) || Collision::AABB(rightWall.getComponent<ColliderComponent>(), *cc) || Collision::AABB(topWall.getComponent<ColliderComponent>(), *cc) || Collision::AABB(bottomWall.getComponent<ColliderComponent>(), *cc))
				{
					cc->entity->destroy();
				}


			}


		}
		UIobject.getComponent<UILabel>().setLabelText("Score. " + to_string(score), 0);
		UIobject.getComponent<UILabel>().setLabelText("HighScore. " + to_string(highScore), 1);
		levels();
		if (score > highScore)
		{
			highScore = score;
		}
	}
	
}
void Game::render()
{
	//render() method renders all textures of entites,maps and UI.
	//PRIMS algorithm is applied here,The object in the background is rendered first.
	SDL_RenderClear(renderer);     
	areaMap->drawMap();	
	if (!gamesOnPause)
	{
		manager.draw();
	}
	UIobject.draw();
	otherActions();
	SDL_RenderPresent(renderer);
}
void Game::clean()
{
	//clean() method destroys objects(Renderer,window,map) before closing the game.
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	areaMap->clearArray();
	SDL_Quit();
	cout << "Game Cleaned" << endl;
}
void Game::createProjectiles(float x, float y, int tagID, Vector2D vec)
{      
	//createProjectiles() method creates projectiles that move around in the game.
	const char* texturePath = "";
	string tagNam;
	switch (tagID)
	{
	case 0:
		texturePath = "assets/texture1.png";
		tagNam = "increase";
		break;
	case 1:
		texturePath = "assets/texture2.png";
		tagNam = "decrease";
		break;
	case 2:
		texturePath = "assets/texture4.png";
		tagNam = "kill";
	default:
		break;
	}
	auto& projectile(manager.addEntity());
	projectile.addComponent<TransformComponent>(x, y, 1, 32, 32);
	projectile.addComponent<SpriteComponent>(texturePath);
	projectile.addComponent<ProjectileComponent>(200, 0, vec);
	projectile.addComponent<ColliderComponent>("projectile");
	projectile.getComponent<ProjectileComponent>().tagName = tagNam;
}
void Game::random(Vector2D vec)
{
	//random() method generates random numbers within the given range to provide for createProjectiles() method to generate projectiles randomly.
	//x range is game width - 2times border
	//y range is game Height - 2times border
	counter = 0;
	int x = rand() % (gameWidth-(border*2)) + (border*2);
	int y = rand() % (gameHeight - (border*2)) + (border*2);
	int texType = rand() % 3 + 0;

	createProjectiles((float)x, (float)y, texType, vec);
}
void Game::otherActions()
{
	//otherActions() method handles UI actions like info screen and restart screen
	if (gamesOnPause or isPlayerDead)
	{
		if (gamesOnPause)
		{
			gameInfo = TextureManager::loadTexture("assets/info.png");
			TextureManager::draw(gameInfo, gameInfosrc, gameInfodes);

		}
		else if (isPlayerDead)
		{
			gameInfo = TextureManager::loadTexture("assets/restart.png");
			TextureManager::draw(gameInfo, gameInfosrc, gameInfodes);
		}
	}
}
void Game::levels()
{
	//levels() methods loads different maps based on level and also increases speed and number of projectiles spawning.
	if (score < 5)
	{
		if (level != 1)
		{
			counterValue = 100;
			projectileSpeed = 0.5;
			areaMap = new Map("level1.txt", gameWidth, gameHeight);
			counter = counterValue;
			level = 1;
		}
		
		
	}
	else if (score < 10)
	{
		if (level != 2)
		{
			counterValue = 75;
			projectileSpeed = 0.75;
			areaMap = new Map("level2.txt", gameWidth, gameHeight);
			counter = counterValue;
			level = 2;
		}
		
	}
	else if (score<15)
	{
		if (level != 3)
		{
			counterValue = 50;
			projectileSpeed = 1.25;
			areaMap = new Map("level3.txt", gameWidth, gameHeight);
			counter = counterValue;
			level = 3;
		}
	}
	else if (score < 20)
	{
		if (level != 4)
		{
			counterValue = 25;
			projectileSpeed = 1.5;
			areaMap = new Map("level4.txt", gameWidth, gameHeight);
			counter = counterValue;
			level = 4;
		}
	}
}