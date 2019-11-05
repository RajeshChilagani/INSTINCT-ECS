/*In Animation.h header file Animation class is defined with constructors
This class stores animation info*/
#pragma once
struct Animation
{
	int index;
	int frames;
	int speed;
	Animation() {}
	Animation(int i,int f,int s)
	{
		index = i;
		frames = f;
		speed = s;
	}
};
