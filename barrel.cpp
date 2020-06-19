#include "pch.h"
#include "barrel.h"

Barrel::Barrel()
{
	this->initVariables();
	this->initTexture();
	this->initAnimation();
	this->initSprite();
}

Barrel::~Barrel()
{
}

void Barrel::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.f) {
		//Collision to the left
		this->velocity.x = 0.f;
	}
	else if (direction.x > 0.f) {
		//Collision to the right
		this->velocity.x = 0.f;
	}
	if (direction.y < 0.f) {
		//Collision on the bottom
		this->velocity.y = 0.f;
	}
	else if (direction.y > 0.f) {
		//Collision on the top
		this->velocity.y = 0.f;
	}
}

void Barrel::update(sf::Time elapsedTime)
{
	this->updateMove(elapsedTime);
	this->updateTexture(elapsedTime);
}

bool Barrel::isOutOfWindow(const sf::RenderTarget* target)
{
	if (this->rebound == 0 && (this->getBounds().left <= 0.f ||
		this->getBounds().left + this->getBounds().width >= target->getSize().x ||
		this->getBounds().top <= 0.f ||
		this->getBounds().top + this->getBounds().height >= target->getSize().y)) {
		return true;
	}
	return false;
}

void Barrel::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	//Left
	if (this->getBounds().left <= 0.f) {
		this->setPosition(0.f + this->getBounds().width / 2, this->getBounds().top + this->getBounds().height / 2);
		this->rebound -= 1;
		this->isMovingLeft = !this->isMovingLeft;
		this->isMovingRight = !this->isMovingRight;
	}
	//Right
	else if (this->getBounds().left + this->getBounds().width >= target->getSize().x) {
		this->setPosition(target->getSize().x - this->getBounds().width / 2, this->getBounds().top + this->getBounds().height / 2);
		this->rebound -= 1;
		this->isMovingLeft = !this->isMovingLeft;
		this->isMovingRight = !this->isMovingRight;
	}
	//Top
	if (this->getBounds().top <= 0.f) {
		this->setPosition(this->getPos().x, 0.f);
		this->rebound -= 1;
		this->isMovingLeft = !this->isMovingLeft;
		this->isMovingRight = !this->isMovingRight;
	}
	//Bottom
	else if (this->getBounds().top + this->getBounds().height >= target->getSize().y) {
		this->setPosition(this->getPos().x, target->getSize().y - this->getBounds().height / 2);
		this->rebound -= 1;
		this->isMovingLeft = !this->isMovingLeft;
		this->isMovingRight = !this->isMovingRight;
	}
}

void Barrel::updateTexture(sf::Time elapsedTime)
{
	this->animatedSprite.update(elapsedTime);
}

void Barrel::updateMove(sf::Time elapsedTime)
{
	this->velocity.x = 0.f;
	this->velocity.y += 981.f * elapsedTime.asSeconds();

	if (this->isMovingLeft) {
		this->velocity.x -= this->movementSpeed;
	}
	if (this->isMovingRight) {
		this->velocity.x += this->movementSpeed;
	}

	this->move(
		this->velocity.x * elapsedTime.asSeconds(),
		this->velocity.y * elapsedTime.asSeconds());
}

void Barrel::move(const float dirX, const float dirY)
{
	this->animatedSprite.move(dirX, dirY);
}

void Barrel::initVariables()
{
	this->movementSpeed = 110.f;
	this->isMovingLeft = false;
	this->isMovingRight = true;
	this->rebound = rand() % 5 + 1;
}

void Barrel::initTexture()
{
	if (!this->texture.loadFromFile("Media/Textures/barrel_anim.png"))
	{
		std::cout << "ERROR::BARREL::INITTEXTURE::Could not load texture file." << "\n";
	}
}

void Barrel::initAnimation()
{
	this->barrelAnimation.setSpriteSheet(this->texture);
	this->barrelAnimation.addFrame(sf::IntRect(0, 0, 14, 12));
	this->barrelAnimation.addFrame(sf::IntRect(15, 0, 14, 12));
	this->barrelAnimation.addFrame(sf::IntRect(30, 0, 14, 12));
	this->barrelAnimation.addFrame(sf::IntRect(45, 0, 14, 12));
}

void Barrel::initSprite()
{
	this->animatedSprite = AnimatedSprite(sf::seconds(0.13f), true, true);
	this->animatedSprite.play(this->barrelAnimation);
	this->animatedSprite.setOrigin(sf::Vector2f(
		this->getPos().x + this->getBounds().width / 2,
		this->getPos().y + this->getBounds().height / 2
	));
	this->animatedSprite.scale(2.f, 2.f);
}
