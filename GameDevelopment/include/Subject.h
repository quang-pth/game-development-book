#pragma once

#include "include/InputObserver.h"
#include<vector>

class ControllerState;

class Subject
{
public:
	Subject();
	virtual ~Subject();
	void AddInputObserver(InputObserver* observer);
	void RemoveInputObserver(InputObserver* observer);
protected:
	void NotifyControllerInput(ControllerState* controller, InputObserver::Event inputEvent);
private:
	InputObserver* mHead;
};

