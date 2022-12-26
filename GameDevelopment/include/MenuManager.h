#pragma once

#include"include/GameObject.h"
#include "include/InputSystem.h"

class MenuManager : public GameObject
{
public:
	MenuManager(class Game* game, const std::string& name = "MenuManager");
	~MenuManager();
	virtual void ProcessGameObjectInput(const InputState& inputState) override;
};

