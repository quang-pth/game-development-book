#include "include/Animation.h"

Animation::Animation(const std::string& name, 
	const std::vector<SDL_Texture*>& textures, bool isLoop)
	: name(name), textures(textures), isLoop(isLoop), mAnimationFPS(24.0f)
{

}

Animation::~Animation()
{
}
