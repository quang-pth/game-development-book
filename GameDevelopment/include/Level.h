#pragma once

#include<include/GameObject.h>

class Level : public GameObject
{
public:
	Level(class Game* game, const std::string& name = "Level");
	~Level();
private:
	void Init();
private:
	std::vector<class Decoration*> mDecorations;
};

