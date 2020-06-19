#pragma once
#include "AnimationSprite.h"

class Entity
{
public:
	Entity();
	~Entity();

	//Accessor
	const sf::Vector2f& getPos() const;
	const sf::Vector2f getPosBottom() const;
	const sf::Vector2f getPosTop() const;
	const sf::FloatRect getBounds() const;

	//Modifiers
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);

	void render(sf::RenderTarget& target);

private:
	virtual void initTexture() = 0;
	virtual void initAnimation() = 0;
	virtual void initSprite() = 0;

public:
	AnimatedSprite animatedSprite;
};

