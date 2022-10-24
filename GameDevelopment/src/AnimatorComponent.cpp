﻿#include "include/AnimatorComponent.h"
#include "include/Animation.h"
#include <iostream>

AnimatorComponent::AnimatorComponent(GameObject* owner, int drawOrder) : 
	SpriteComponent(owner, drawOrder), mCurrentFrame(0), mAnimationsMap()
{

}

AnimatorComponent::~AnimatorComponent()
{
}

void AnimatorComponent::Update(float deltaTime)
{
	const std::shared_ptr<Animation> animation = mAnimationsMap[mAnimationName];
	const std::vector<SDL_Texture*> textures = animation->mTextures;
	const int animationFrames = textures.size();
	
	if (animationFrames < 0) return;

	mCurrentFrame += animation->GetFPS() * deltaTime;

	while (mCurrentFrame >= animationFrames) {
		mCurrentFrame -= animationFrames;
		
		if (!animation->mIsLoop) {
			SetAnimation("Walk");
			return;
		}
	}

	SpriteComponent::SetTexture(textures[static_cast<int>(mCurrentFrame)]);
}

void AnimatorComponent::SetAnimation(const std::string& animationName)
{
	if (animationName == mAnimationName) return;
	
	if (mAnimationsMap.find(animationName) == mAnimationsMap.end()) {
		std::cout << "No animation name found" << std::endl;
		return;
	}

	ResetAnimation(animationName);
}

void AnimatorComponent::AddAnimation(const std::string& animationName, std::shared_ptr<Animation> animation)
{
	mAnimationsMap.insert({animationName, animation});
}

void AnimatorComponent::ResetAnimation(std::string animationName)
{
	mAnimationName = animationName;
	mCurrentFrame = 0;
}
