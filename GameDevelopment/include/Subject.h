#pragma once

#include "include/InputObserver.h"
#include<vector>

class Subject
{
public:
	Subject();
	virtual ~Subject();
	void AddObserver(Observer* observer);
	void RemoveObserver(Observer* observer);
	virtual Observer* GetHead() const { return nullptr; };
	virtual void SetHead(Observer* head) {};
};

