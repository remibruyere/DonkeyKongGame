#pragma once
#include "Entity.h"

class Ladder: public Entity
{
public:
	Ladder();
	virtual ~Ladder();

private:
	// Extend from Entity
	virtual void initTexture() override;
	virtual void initSprite() override;
};