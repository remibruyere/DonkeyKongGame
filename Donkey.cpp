#include "pch.h"
#include "Donkey.h"

Donkey::Donkey()
{
	this->initVariable();
	this->initTexture();
	this->initAnimation();
	this->initSprite();
}

Donkey::~Donkey()
{
}

void Donkey::update(sf::Time elapsedTime)
{
	this->updateTexture(elapsedTime);
}

void Donkey::spawnBarrel(sf::Time elapsedTime, std::vector<Barrel*>& barrels)
{
	this->lastSpawnBarrelTime += elapsedTime;
	//std::cout << this->animatedSprite.getCurrentFrame() << std::endl;
	if (this->lastSpawnBarrelTime >= sf::seconds(3.f) && this->animatedSprite.getCurrentFrame() == 3) {
		this->lastSpawnBarrelTime = sf::seconds(0.f);
		Barrel* barrel = new Barrel();
		barrel->setPosition(
			this->getPosBottom().x + this->getBounds().width / 2 + barrel->getBounds().width / 2,
			this->getPosBottom().y - barrel->getBounds().height / 2
		);
		//std::cout << "spawn barrel" << std::endl;
		barrels.push_back(barrel);
	}
}

void Donkey::updateTexture(sf::Time elapsedTime) {
	this->animatedSprite.update(elapsedTime);
}

void Donkey::initTexture()
{
	if (!this->texture.loadFromFile("Media/Textures/donkey_anim.png"))
	{
		std::cout << "ERROR::DONKEY::INITTEXTURE::Could not load texture file." << "\n";
	}
}

void Donkey::initAnimation()
{
	this->throwBarrelAnimation.setSpriteSheet(this->texture);
	this->throwBarrelAnimation.addFrame(sf::IntRect(0, 0, 42, 34));
	this->throwBarrelAnimation.addFrame(sf::IntRect(43, 0, 45, 34));
	this->throwBarrelAnimation.addFrame(sf::IntRect(89, 0, 42, 34));
	this->throwBarrelAnimation.addFrame(sf::IntRect(132, 0, 45, 34));
}

void Donkey::initSprite()
{
	this->animatedSprite = AnimatedSprite(sf::seconds(1.f), false, true);
	this->animatedSprite.setAnimation(this->throwBarrelAnimation);
	this->animatedSprite.setOrigin(sf::Vector2f(
		this->getPos().x + this->getBounds().width / 2,
		this->getPos().y + this->getBounds().height / 2
	));
	this->animatedSprite.scale(2.f, 2.f);
}

void Donkey::initVariable()
{
	this->lastSpawnBarrelTime = sf::seconds(0.f);
}
