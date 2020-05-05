#include "pch.h"
#include "Player.h"

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
}

void Player::setOverLadder(bool isOverLadder)
{
	if (this->isOverLadder != isOverLadder)
		this->isOverLadder = isOverLadder;
}

void Player::updateInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Up)
		this->isMovingUp = isPressed;
	else if (key == sf::Keyboard::Down)
		this->isMovingDown = isPressed;
	else if (key == sf::Keyboard::Left)
		this->isMovingLeft = isPressed;
	else if (key == sf::Keyboard::Right)
		this->isMovingRight = isPressed;

	if (key == sf::Keyboard::Space)
	{
	}
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	//Left
	if (this->getBounds().left <= 0.f)
		this->setPosition(0.f, this->getBounds().top);
	//Right
	else if (this->getBounds().left + this->getBounds().width >= target->getSize().x)
		this->setPosition(target->getSize().x - this->getBounds().width, this->getBounds().top);
	//Top
	if (this->getBounds().top <= 0.f)
		this->setPosition(this->getBounds().left, 0.f);
	//Bottom
	else if (this->getBounds().top + this->getBounds().height >= target->getSize().y)
		this->setPosition(this->getBounds().left, target->getSize().y - this->getBounds().height);
}

void Player::updateMove(sf::Time elapsedTime) {
	sf::Vector2f movement(0.f, 0.f);
	if (this->isMovingUp)
		movement.y -= 1.f;
	if (this->isMovingDown)
		movement.y += 1.f;
	if (this->isMovingLeft)
		movement.x -= 1.f;
	if (this->isMovingRight)
		movement.x += 1.f;

	this->move(movement.x * elapsedTime.asSeconds(), movement.y * elapsedTime.asSeconds());
}

void Player::update(sf::Time elapsedTime)
{
	this->updateMove(elapsedTime);
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

void Player::initVariables()
{
	this->alive = true;
	this->movementSpeed = 200.f;
	this->isMovingUp = false;
	this->isMovingDown = false;
	this->isMovingLeft = false,
	this->isMovingRight = false;
	this->isOverLadder = false;
	this->isClimbing = false;
}

void Player::initTexture()
{
	if (!this->texture.loadFromFile("Media/Textures/Mario_small_transparent.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
	}
}

void Player::initSprite()
{
	this->sprite.setTexture(this->texture);
	//this->sprite.scale(0.1f, 0.1f);
}