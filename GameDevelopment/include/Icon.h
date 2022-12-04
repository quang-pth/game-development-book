#pragma once

#include<include/GameObject.h>

class Icon : public GameObject
{
public:
	Icon(class Game* game, const std::string& name = "Icon");
	~Icon();
	void SetTexture(class Texture* texture);
private:
	class SpriteComponent* spriteComponent;
	class Texture* mTexture;
};

