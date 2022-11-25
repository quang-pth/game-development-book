#pragma once

#include<SDL2/SDL.h>
#include <string>
#include <vector>

class Animation
{
public:
	Animation(const std::string& name, const std::vector<class Texture*>& textures, bool isLoop = true);
	~Animation();
	float GetFPS() const { return mAnimationFPS; }
	void SetFPS(float fps) { mAnimationFPS = fps; }
	bool mIsLoop;
	std::vector<class Texture*> mTextures;
private:
	float mAnimationFPS;
	std::string mName;
};