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
	return this->sprite.getPosition();
}

const sf::Vector2f Entity::getPosMiddle() const
{
	return sf::Vector2f(
		this->getPos().x + this->getBounds().width / 2,
		this->getPos().y + this->getBounds().height / 2
	);
}

const sf::FloatRect Entity::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Entity::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Entity::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
