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
	this->canClimb = isOverLadder;
}

void Player::OnCollision(sf::Vector2f direction)
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
		this->canJump = true;
	}
	else if (direction.y > 0.f) {
		//Collision on the top
		this->velocity.y = 0.f;
	}
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

	if (key == sf::Keyboard::Space && this->canJump)
	{
		this->canJump = false;
		this->velocity.y = -sqrtf(2.f * 981.f * this->jumpHeight);
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

void Player::updateMove(sf::Time elapsedTime) 
{
	if (this->isClimbing && !this->canClimb) {
		this->isClimbing = false;
	}
	this->velocity.x = 0.f;
	if (!this->isClimbing) {
		this->velocity.y += 981.f * elapsedTime.asSeconds();
	} else {
		this->velocity.y = 0;
	}
	if (this->canClimb) {
		if (this->isMovingUp) {
			this->velocity.y = -this->movementSpeed;
			this->isClimbing = true;
		}
		if (this->isMovingDown) {
			this->velocity.y = 0;
			this->velocity.y = this->movementSpeed;
		}
	}
	if (!this->isClimbing) {
		if (this->isMovingLeft) {
			this->velocity.x -= this->movementSpeed;
		}
		if (this->isMovingRight) {
			this->velocity.x += this->movementSpeed;
		}
	}

	this->move(
		this->velocity.x * elapsedTime.asSeconds(), 
		this->velocity.y * elapsedTime.asSeconds());
}

void Player::update(sf::Time elapsedTime)
{
	this->updateMove(elapsedTime);
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(dirX, dirY);
}

void Player::initVariables()
{
	this->alive = true;
	this->movementSpeed = 200.f;
	this->isMovingUp = false;
	this->isMovingDown = false;
	this->isMovingLeft = false,
	this->isMovingRight = false;
	this->canClimb = false;
	this->isClimbing = false;
	this->canJump = true;
	this->jumpHeight = 35.f;
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