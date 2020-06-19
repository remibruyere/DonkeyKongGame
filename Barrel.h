#pragma once
#include "Entity.h"

class Barrel : public Entity
{
public:
	Barrel();
	virtual ~Barrel();

	void OnCollision(sf::Vector2f direction);

	void update(sf::Time elapsedTime);
	bool isOutOfWindow(const sf::RenderTarget* target);
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void updateTexture(sf::Time elapsedTime);
	void updateMove(sf::Time elapsedTime);

private:
	// Extend from Entity
	virtual void initTexture() override;
	virtual void initAnimation() override;
	virtual void initSprite() override;

	//Functions
	void initVariables();
	void move(const float dirX, const float dirY);

private:
	float movementSpeed;

	sf::Texture texture;
	Animation barrelAnimation;

	sf::Vector2f velocity;
	bool isMovingRight;
	bool isMovingLeft;

	int rebound;
};