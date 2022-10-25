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
	void AddAnimation(const std::string& animationName, std::shared_ptr<class Animation> animation);
	void ResetAnimation(std::string animationName);
private:
	std::unordered_map <std::string, std::shared_ptr<class Animation>> mAnimationsMap;
	std::string mAnimationName;
	float mCurrentFrame;
};

