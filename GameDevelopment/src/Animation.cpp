#include "include/Animation.h"
#include "include/Texture.h"

Animation::Animation(const std::string& name, const std::vector<Texture*>& textures, bool isLoop)
	: mName(name), mTextures(textures), mIsLoop(isLoop), mAnimationFPS(24.0f)
{

}

Animation::~Animation()
{
}
