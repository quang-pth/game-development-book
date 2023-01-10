#include "include/InputSubject.h"
#include "include/InputObserver.h"

InputSubject::InputSubject() : 
	Subject(), mHead(nullptr)
{
}

InputSubject::~InputSubject()
{
}

void InputSubject::NotifyControllerInput(ControllerState* controller, InputObserver::Event inputEvent)
{
	InputObserver* iter = mHead;
	while (iter != nullptr) {
		iter->OnControllerInputHandler(controller, inputEvent);
		iter = iter->mNext;
	}
}