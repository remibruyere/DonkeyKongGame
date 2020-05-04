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

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

void Player::initVariables()
{
	this->alive = true;
	this->movementSpeed = 2.f;
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