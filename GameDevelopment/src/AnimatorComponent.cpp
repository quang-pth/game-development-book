#include "include/AnimatorComponent.h"
#include "include/Animation.h"
#include <iostream>

AnimatorComponent::AnimatorComponent(GameObject* owner, int drawOrder) : 
	SpriteComponent(owner, drawOrder), 
	mCurrentFrame(0), 
	mAnimationsMap(), mCurrentAnimation()
{

}

AnimatorComponent::~AnimatorComponent()
{
}

void AnimatorComponent::Update(float deltaTime)
{
	mCurrentAnimation = mAnimationsMap[mAnimationName];
	const std::vector<SDL_Texture*> textures = mCurrentAnimation->textures;
	const int animationFrames = textures.size();
	
	if (animationFrames < 0) return;

	mCurrentFrame += mCurrentAnimation->GetFPS() * deltaTime;

	while (mCurrentFrame >= animationFrames) {
		mCurrentFrame -= animationFrames;
		
		if (!mCurrentAnimation->isLoop) {
			mCurrentFrame = textures.size() - 1;
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

void AnimatorComponent::AddAnimation(std::shared_ptr<Animation> animation)
{
	mAnimationsMap.insert({animation->name, animation});
}

void AnimatorComponent::ResetAnimation(std::string animationName)
{
	mAnimationName = animationName;
	mCurrentFrame = 0;
}

bool AnimatorComponent::IsFinishedAnimation()
{
	return mCurrentAnimation->IsFinished(mCurrentFrame);
}
