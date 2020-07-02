#include "pch.h"
#include "Ladder.h"

Ladder::Ladder()
{
	this->initTexture();
	this->initAnimation();
	this->initSprite();
}

Ladder::~Ladder()
{
}

void Ladder::initTexture()
{
	if (!this->texture.loadFromFile("Media/Textures/ladder.png"))
	{
		std::cout << "ERROR::LADDER::INITTEXTURE::Could not load texture file." << "\n";
	}
}

void Ladder::initAnimation()
{
	this->ladderAnimation.setSpriteSheet(this->texture);
	this->ladderAnimation.addFrame(sf::IntRect(0, 0, 10, 9));
	this->ladderAnimation.addFrame(sf::IntRect(0, 12, 10, 8));
	this->ladderAnimation.addFrame(sf::IntRect(0, 19, 10, 9));
}


void Ladder::initSprite()
{
	this->animatedSprite = AnimatedSprite(sf::seconds(0.f), true, false);
	this->animatedSprite.setAnimation(this->ladderAnimation);
	this->animatedSprite.setOrigin(sf::Vector2f(
		this->getPos().x + this->getBounds().width / 2,
		this->getPos().y + this->getBounds().height / 2
	));
	this->animatedSprite.scale(2.f, 2.f);
}