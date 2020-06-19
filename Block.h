#pragma once
#include "Entity.h"

class Block: public Entity
{
public:
	Block();
	virtual ~Block();

private:
	// Extend from Entity
	virtual void initTexture() override;
	virtual void initAnimation() override;
	virtual void initSprite() override;

private:
	sf::Texture texture;
	Animation blockAnimation;
};

