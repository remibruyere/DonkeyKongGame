#pragma once
#include "Entity.h"

class StaticBarrel : public Entity
{
public:
	StaticBarrel();
	virtual ~StaticBarrel();

private:
	// Extend from Entity
	virtual void initTexture() override;
	virtual void initAnimation() override;
	virtual void initSprite() override;

private:
	sf::Texture texture;
	Animation blockAnimation;
};



