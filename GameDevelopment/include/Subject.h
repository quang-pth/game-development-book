#pragma once

#include "include/InputObserver.h"
#include<vector>

class Subject
{
public:
	Subject();
	virtual ~Subject();
	void AddInputObserver(Observer* observer);
	void RemoveInputObserver(Observer* observer);
	virtual Observer* GetHead() const { return nullptr; };
	virtual void SetHead(Observer* head) {};
};

