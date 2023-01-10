#pragma once

#include"include/CustomMath.h"
#include"include/Subject.h"

class GameObject;
class GameObjectObserver;

class GameObjectSubject : public Subject
{
public:
	GameObjectSubject();
	virtual Observer* GetHead() const override;
	virtual void SetHead(Observer* head) override;
protected:
	void OnFireNotify(GameObject* gameObject, const Vector3& fireDirection);
private:
	GameObjectObserver* mHead;
};

