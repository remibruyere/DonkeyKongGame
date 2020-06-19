#include "pch.h"
#include "StaticBarrel.h"

StaticBarrel::StaticBarrel()
{
	this->initTexture();
	this->initAnimation();
	this->initSprite();
}

StaticBarrel::~StaticBarrel()
{
}

void StaticBarrel::initTexture()
{
	if (!this->texture.loadFromFile("Media/Textures/barrel_static.png"))
	{
		std::cout << "ERROR::STATICBARREL::INITTEXTURE::Could not load texture file." << "\n";
	}
}

void StaticBarrel::initAnimation()
{
	this->blockAnimation.setSpriteSheet(this->texture);
	this->blockAnimation.addFrame(sf::IntRect(0, 0, 12, 18));
}


void StaticBarrel::initSprite()
{
	this->animatedSprite = AnimatedSprite(sf::seconds(0.f), true, false);
	this->animatedSprite.setAnimation(this->blockAnimation);
	this->animatedSprite.setOrigin(sf::Vector2f(
		this->getPos().x + this->getBounds().width / 2,
		this->getPos().y + this->getBounds().height / 2
	));
	this->animatedSprite.scale(2.f, 2.f);
}
