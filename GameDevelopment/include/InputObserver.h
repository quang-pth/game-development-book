#pragma once

#include"include/Observer.h"

class ControllerState;

class InputObserver : public Observer
{
	friend class Subject;
	friend class InputSubject;
public:
	enum class Event {
		EAdded,
		ERemoved
	};
	virtual ~InputObserver() = default;
	virtual void OnControllerInputHandler(ControllerState* controller, Event inputEvent) = 0;
	virtual Observer* GetNext() const override { return mNext; }
	virtual Observer* GetPrev() const override { return mPrev; }
	virtual void SetNext(Observer* next) override { mNext = dynamic_cast<InputObserver*>(next); }
	virtual void SetPrev(Observer* prev) override { mPrev = dynamic_cast<InputObserver*>(prev); }
protected:
	InputObserver* mPrev = nullptr;
	InputObserver* mNext = nullptr;
};
