#pragma once

#include<include/SpriteComponent.h>
#include<unordered_map>
#include<memory>

class AnimatorComponent : public SpriteComponent
{
public:
	AnimatorComponent(class GameObject* owner, int drawOrder = 100);
	~AnimatorComponent();
	void Update(float deltaTime) override;
	void SetAnimation(const std::string& animationName);
	void AddAnimation(std::shared_ptr<class Animation> animation);
	void ResetAnimation(std::string animationName);
	bool IsFinishedAnimation();
private:
	std::unordered_map <std::string, std::shared_ptr<class Animation>> mAnimationsMap;
	std::shared_ptr<class Animation> mCurrentAnimation;
	std::string mAnimationName;
	float mCurrentFrame;
};
