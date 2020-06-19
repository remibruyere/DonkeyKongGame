#pragma once
#include "Entity.h"
#include "Animation.h"
#include "AnimationSprite.h"

class Player: public Entity
{
public:
	Player();
	virtual ~Player();

	void setOverLadder(bool isOverLadder);

	void setScaleToRight();

	void setScaleToLeft();

	void OnCollision(sf::Vector2f direction);

	void updateTexture(sf::Time elapsedTime);
	void updateInput(sf::Keyboard::Key key, bool isPressed);
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void updateMove(sf::Time elapsedTime);
	void update(sf::Time elapsedTime);

public:
	bool isClimbing;
	bool alive;

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

	bool isMovingUp;
	bool isMovingDown;
	bool isMovingRight;
	bool isMovingLeft;

	bool canClimb;
	
	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;

	sf::Texture textureWalk;
	sf::Texture textureJump;
	sf::Texture textureClimb;

	Animation walkingAnimation;

	Animation jumpAnimation;

	Animation climbAnimation;

	Animation* currentAnimation;
};

