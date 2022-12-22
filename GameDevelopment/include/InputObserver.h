#pragma once

class ControllerState;

class InputObserver
{
	friend class Subject;
public:
	enum class Event {
		EAdded,
		ERemoved
	};
	virtual ~InputObserver() = default;
	virtual void OnControllerInputHandler(ControllerState* controller, Event inputEvent) = 0;
private:
	InputObserver* mPrev = nullptr;
	InputObserver* mNext = nullptr;
};

