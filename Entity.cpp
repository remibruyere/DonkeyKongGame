#include "pch.h"
#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

const sf::Vector2f& Entity::getPos() const
{
	return this->animatedSprite.getPosition();
}

const sf::Vector2f Entity::getPosBottom() const
{
	return sf::Vector2f(
		this->getPos().x,
		this->getPos().y + this->getBounds().height / 2
	);
}

const sf::Vector2f Entity::getPosTop() const
{
	return sf::Vector2f(
		this->getPos().x,
		this->getPos().y - this->getBounds().height / 2
	);
}

const sf::FloatRect Entity::getBounds() const
{
	return this->animatedSprite.getGlobalBounds();
}

void Entity::setPosition(const sf::Vector2f pos)
{
	//std::cout << "set pos" << pos.x << ":" << pos.y << std::endl;
	this->animatedSprite.setPosition(pos);
}

void Entity::setPosition(const float x, const float y)
{
	//std::cout << "set pos" << x << ":" << y << std::endl;
	this->animatedSprite.setPosition(x, y);
}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(this->animatedSprite);
}
