#pragma once

#include"include/Subject.h"

class InputObserver;

class InputSubject : public Subject
{
public:
	InputSubject();
	~InputSubject();
	virtual InputObserver* GetHead() const override { return mHead; };
	virtual void SetHead(Observer* head) override { mHead = dynamic_cast<InputObserver*>(head); }
protected:
	void NotifyControllerInput(ControllerState* controller, InputObserver::Event inputEvent);
private:
	InputObserver* mHead;
};

