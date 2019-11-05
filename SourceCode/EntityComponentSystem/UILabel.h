/*In UILabel.h header file UILabel class is defined with constructors and members
TransformComponent class inherits from base class Component in EntityComponentSystem.h.draw() method overrides base class method
UIelements are managed using this Component.Multiple ui lables can be added to one entity*/
#pragma once
#include "SDL_ttf.h"
#include "EntityComponentSystem.h"
#include "../TextureManager.h"
#include "../game.h"
#include<string>
#include <map>
#include<vector>
class UILabel:public Component
{
private:
	vector<SDL_Rect> labelRects;
	vector<SDL_Texture*> labelTextures;
	SDL_Rect position;
	std::string fontPath;
	SDL_Color textColor;
	SDL_Texture* labelTexture;
	TTF_Font* font;
public:
	UILabel(std::string path,SDL_Color& color,int fontSize):fontPath(path),textColor(color)
	{

		font = TTF_OpenFont(fontPath.c_str(),fontSize);
	    

	}
	~UILabel()
	{

	}
	void addLabel(int xpos,int ypos,string labeltext)
	{
		position.x = xpos;
		position.y = ypos;
		SDL_Surface* surf = TTF_RenderText_Blended(font, labeltext.c_str(), textColor);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		SDL_FreeSurface(surf);
		labelTextures.push_back(labelTexture);
		labelRects.push_back(position);
		SDL_QueryTexture(labelTexture, nullptr, nullptr, &labelRects[labelRects.size()-1].w, &labelRects[labelRects.size() - 1].h);
	}
	void setLabelText(string labelText,int index)
	{
		SDL_Surface* surf = TTF_RenderText_Blended(font,labelText.c_str(),textColor);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer,surf);
		labelTextures[index] = labelTexture;
		SDL_FreeSurface(surf);
		SDL_QueryTexture(labelTexture, nullptr, nullptr, &labelRects[index].w, &labelRects[index].h);
	}
	void draw() override
	{
		
		for (int i = 0; i < labelRects.size(); i++)
		{
			SDL_RenderCopy(Game::renderer, labelTextures[i], nullptr, &labelRects[i]);
		}
		
			
		
	}
};
