#pragma once

#include<SDL2/SDL.h>
#include <string>
#include <vector>

class Animation
{
public:
	bool isLoop;
	std::vector<SDL_Texture*> textures;
	std::string name;
	Animation(const std::string& name, const std::vector<SDL_Texture*>& textures, bool isLoop = true);
	~Animation();
	float GetFPS() const { return mAnimationFPS; }
	void SetFPS(float fps) { mAnimationFPS = fps; }
private:
	float mAnimationFPS;
};
