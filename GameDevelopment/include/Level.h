#pragma once

#include<include/GameObject.h>

class Level : public GameObject
{
public:
	Level(class Game* game, const std::string& name = "Level");
	~Level();
	const std::vector<class Decoration*>& GetPlanes() const { return mDecorations; }
private:
	void Init();
private:
	std::vector<class Decoration*> mDecorations;
};

