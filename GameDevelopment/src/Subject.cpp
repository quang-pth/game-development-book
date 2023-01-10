#include "include/Subject.h"

Subject::Subject()
{
}

Subject::~Subject()
{
	Observer* head = this->GetHead();
	Observer* iter = head;

	while (iter != nullptr) {
		head = iter->GetNext();

		iter->SetPrev(nullptr);
		iter->SetNext(nullptr);
		delete iter;

		iter = head;
	}
}

void Subject::AddInputObserver(Observer* observer)
{
	Observer* head = this->GetHead();

	if (head == nullptr) {
		this->SetHead(observer);
	}
	else {
		observer->SetNext(head);
		head->SetPrev(observer);
		this->SetHead(observer);
	}
}

void Subject::RemoveInputObserver(Observer* observer)
{
	Observer* head = this->GetHead();

	if (observer == nullptr || head == nullptr) return;

	if (observer == head) {
		this->SetHead(observer->GetNext());
	}
	else if (observer->GetNext() == nullptr) {
		observer->GetPrev()->SetNext(nullptr);
	}
	else {
		observer->GetNext()->SetPrev(observer->GetPrev());
		observer->GetPrev()->SetNext(observer->GetNext());
	}

	observer->SetNext(nullptr);
	observer->SetPrev(nullptr);
}