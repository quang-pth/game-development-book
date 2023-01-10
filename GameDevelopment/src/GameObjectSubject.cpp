#include "include/GameObjectSubject.h"
#include "include/GameObject.h"
#include"include/GameObjectObserver.h"

GameObjectSubject::GameObjectSubject() : Subject(), mHead(nullptr)
{
}

Observer* GameObjectSubject::GetHead() const
{
	return mHead;
}

void GameObjectSubject::SetHead(Observer* head)
{
	mHead = dynamic_cast<GameObjectObserver*>(head);
}

void GameObjectSubject::OnFireNotify(GameObject* gameObject, const Vector3& fireDirection)
{
	GameObjectObserver* iter = mHead;
	while (iter != nullptr) {
		iter->OnFireNotifyHandler(gameObject, fireDirection);
		iter = iter->mNext;
	}
}
