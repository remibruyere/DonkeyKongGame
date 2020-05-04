#pragma once
#include "Entity.h"

class Player: public Entity
{
public:
	Player();
	virtual ~Player();

	//Functions
	void move(const float dirX, const float dirY);

private:
	// Extend from Entity
	virtual void initTexture() override;
	virtual void initSprite() override;

	//Functions
	void initVariables();

private:
	float movementSpeed;
	bool alive;
};

