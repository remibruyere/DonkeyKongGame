#pragma once
#include "Entity.h"
#include "Barrel.h"

class Donkey : public Entity
{
public:
	Donkey();
	virtual ~Donkey();

	void update(sf::Time elapsedTime);

	void spawnBarrel(sf::Time elapsedTime, std::vector<Barrel*>& barrels);

	void updateTexture(sf::Time elapsedTime);

private:
	// Extend from Entity
	virtual void initTexture() override;
	virtual void initAnimation() override;
	virtual void initSprite() override;

	void initVariable();

private:
	sf::Texture texture;
	Animation throwBarrelAnimation;

	sf::Time lastSpawnBarrelTime;
};