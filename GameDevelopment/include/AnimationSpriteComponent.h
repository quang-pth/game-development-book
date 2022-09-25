#pragma once

#include<include/SpriteComponent.h>

class AnimationSpriteComponent : public SpriteComponent
{
public:
	AnimationSpriteComponent(class Actor* owner, int drawOrder = 100);
	void Update(float deltaTime);
	void SetAnimationTextures(const std::vector<SDL_Texture*>& textures);
	float GetAnimationFPS() { return mAnimationFPS; }
	void SetAnimationFPS(float fps) { mAnimationFPS = fps; }
private:
	std::vector<SDL_Texture*> mAnimationTextures;
	int mCurrentFrame;
	float mAnimationFPS;
};

