#pragma once

class Observer
{
public:
	Observer() = default;
	virtual ~Observer() = default;
	virtual Observer* GetNext() const = 0;
	virtual Observer* GetPrev() const = 0;
	virtual void SetNext(Observer* next) = 0;
	virtual void SetPrev(Observer* prev) = 0;
};
