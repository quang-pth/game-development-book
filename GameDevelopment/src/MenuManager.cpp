#include "include/MenuManager.h"
#include "include/Game.h"
#include "include/InputComponent.h"

MenuManager::MenuManager(Game* game, const std::string& name) :
	GameObject(game, name)
{
}

MenuManager::~MenuManager()
{
}

void MenuManager::ProcessGameObjectInput(const InputState& inputState)
{
	const InputSystem* inputSystem = GameObject::GetGame()->GetInputSystem();
	// ========================= START CONTROLLER INPUT ========================
	for (const ControllerState& controllerState : inputState.Controllers) {
		if (!controllerState.GetIsConnected() || !controllerState.GetIsUsed()) continue;
		
		if (inputSystem->GetMappedButtonState("Quit", &controllerState) == ButtonState::EReleased) 
		{
			GameObject::GetGame()->SetIsRunning(false);
			return;
		}
	}
	// ========================= END CONTROLLER INPUT ========================
	// =======================================================================
	// ========================= KEYBOARD INPUT ========================
	if (inputSystem->GetMappedKeyState("Quit") == ButtonState::EReleased) {
		GameObject::GetGame()->SetIsRunning(false);
		return;
	}
	// ========================= END KEYBOARD INPUT ========================
	// =======================================================================
}