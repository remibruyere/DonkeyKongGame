#pragma once
#include "Entity.h"

class Player: public Entity
{
public:
	Player();
	virtual ~Player();

	void setOverLadder(bool isOverLadder);

	void OnCollision(sf::Vector2f direction);

	void updateInput(sf::Keyboard::Key key, bool isPressed);
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void updateMove(sf::Time elapsedTime);
	void update(sf::Time elapsedTime);

public:
	bool isClimbing;

private:
	// Extend from Entity
	virtual void initTexture() override;
	virtual void initSprite() override;

	//Functions
	void initVariables();
	void move(const float dirX, const float dirY);

private:
	float movementSpeed;
	bool alive;

	bool isMovingUp;
	bool isMovingDown;
	bool isMovingRight;
	bool isMovingLeft;

	bool canClimb;
	
	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;

};

