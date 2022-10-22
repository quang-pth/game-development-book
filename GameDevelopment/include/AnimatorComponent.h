#pragma once

#include<include/SpriteComponent.h>
#include<unordered_map>

class AnimatorComponent : public SpriteComponent
{
public:
	AnimatorComponent(class GameObject* owner, int drawOrder = 100);
	~AnimatorComponent();
	void Update(float deltaTime) override;
	void SetAnimation(const std::string& animationName);
	void AddAnimation(const std::string& animationName, class Animation* animation);
	void ResetAnimation(std::string animationName);
private:
	std::unordered_map<std::string, class Animation*> mAnimationsMap;
	std::string mAnimationName;
	float mCurrentFrame;
};

