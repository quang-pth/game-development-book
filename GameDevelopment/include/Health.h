#pragma once


class Health
{
public:
	Health(float health);
	~Health();
	void ReceiveDamage(float amount);
	void Recover(float amount);
	bool IsDead() const;
	float GetHealth() const;
	void SetHealth(float amount);
private:
	float mHealth;
};

