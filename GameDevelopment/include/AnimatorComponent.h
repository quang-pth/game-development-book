#pragma once

#include<include/SpriteComponent.h>
#include<unordered_map>

class AnimatorComponent : public SpriteComponent
{
public:
	AnimatorComponent(class GameObject* owner, int drawOrder = 100);
	AnimatorComponent(const AnimatorComponent& other);
	~AnimatorComponent();
	void Update(float deltaTime) override;
	void SetAnimation(const std::string& animationName);
	void AddAnimation(const std::string& animationName, class Animation* animation);
	void ResetAnimationFrame();
private:
	//std::unordered_map<std::string, std::vector<SDL_Texture*>> mAnimations;
	std::unordered_map<std::string, class Animation*> mAnimationsMap;
	std::string mAnimationName;
	float mCurrentFrame;
};

