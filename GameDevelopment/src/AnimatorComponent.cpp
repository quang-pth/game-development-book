#include "include/AnimatorComponent.h"
#include "include/Animation.h"
#include <iostream>

AnimatorComponent::AnimatorComponent(GameObject* owner, int drawOrder) : 
	SpriteComponent(owner, drawOrder), mCurrentFrame(0), mAnimationsMap()
{

}

AnimatorComponent::AnimatorComponent(const AnimatorComponent& other)
{
}

AnimatorComponent::~AnimatorComponent()
{
}

void AnimatorComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	const Animation* animation = mAnimationsMap[mAnimationName];
	const std::vector<SDL_Texture*> textures = animation->mTextures;
	const int animationFrames = textures.size();
	
	if (animationFrames < 0) return;

	mCurrentFrame += animation->GetFPS() * deltaTime;
	if (mCurrentFrame > animationFrames) {
		ResetAnimationFrame();

		if (!animation->mIsLoop) {
			SetAnimation("Walk");
			return;
		}
	}

	SetTexture(textures[static_cast<int>(mCurrentFrame)]);
}

void AnimatorComponent::SetAnimation(const std::string& animationName)
{
	if (mAnimationsMap.find(animationName) == mAnimationsMap.end()) {
		std::cout << "No animation name found" << std::endl;
		return;
	}

	mAnimationName = animationName;
}

void AnimatorComponent::AddAnimation(const std::string& animationName, Animation* animation)
{
	mAnimationsMap.insert({animationName, animation});
}

void AnimatorComponent::ResetAnimationFrame()
{
	mCurrentFrame = 0;
}
