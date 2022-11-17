#include "Health.h"

Health::Health(float health) : mHealth(health)
{
}

Health::~Health()
{
}

void Health::ReceiveDamage(float amount)
{
    mHealth -= amount;
}

void Health::Recover(float amount)
{
    mHealth += amount;
}

bool Health::IsDead() const
{
    return mHealth <= 0.0f;
}

float Health::GetHealth() const
{
    return mHealth;
}

void Health::SetHealth(float amount)
{
    mHealth = amount;
}
