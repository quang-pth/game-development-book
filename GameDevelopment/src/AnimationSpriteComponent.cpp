#include "include/AnimationSpriteComponent.h"
#include <iostream>

AnimationSpriteComponent::AnimationSpriteComponent(Actor* owner, int drawOrder) : 
	SpriteComponent(owner, drawOrder), mCurrentFrame(0), mAnimationTextures(), mAnimationFPS(24.0f)
{

}

void AnimationSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);
	
	const int animationFrames = mAnimationTextures.size();
	if (animationFrames > 0) {
		mCurrentFrame += mAnimationFPS * deltaTime;

		while (mCurrentFrame > animationFrames) {
			mCurrentFrame -= animationFrames;
		}

		int currentAnimationFrame = static_cast<int>(mCurrentFrame);

		SDL_Texture* currentTexture = mAnimationTextures[currentAnimationFrame];
		SetTexture(currentTexture);
	}
}

void AnimationSpriteComponent::SetAnimationTextures(const std::vector<SDL_Texture*>& textures)
{
	mAnimationTextures = textures;
	mCurrentFrame = 0;
	SetTexture(mAnimationTextures[mCurrentFrame]);
}
