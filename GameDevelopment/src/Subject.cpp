#include "include/Subject.h"

Subject::Subject() : mHead(nullptr)
{
}

Subject::~Subject()
{
	InputObserver* iter = mHead;
	while (iter != nullptr) {
		mHead = iter->mNext;

		iter->mPrev = nullptr;
		iter->mNext = nullptr;
		delete iter;

		iter = mHead;
	}
}

void Subject::AddInputObserver(InputObserver* observer)
{
	if (mHead == nullptr) {
		mHead = observer;
	}
	else {
		observer->mNext = mHead;
		mHead->mPrev = observer;
		mHead = observer;
	}
}

void Subject::RemoveInputObserver(InputObserver* observer)
{
	if (observer == nullptr || mHead == nullptr) return;

	if (observer == mHead) {
		mHead = observer->mNext;
	}
	else if (observer->mNext == nullptr) {
		observer->mPrev->mNext = nullptr;
	}
	else {
		observer->mNext->mPrev = observer->mPrev;
		observer->mPrev->mNext = observer->mNext;
	}

	observer->mNext = nullptr;
	observer->mPrev = nullptr;
}

void Subject::Notify(ControllerState* controller, InputObserver::Event inputEvent)
{
	InputObserver* iter = mHead;
	while (iter != nullptr) {
		iter->OnNotify(controller, inputEvent);
		iter = iter->mNext;
	}
}