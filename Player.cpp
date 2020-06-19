#include "pch.h"
#include "Player.h"

Player::Player()
{
	this->initTexture();
	this->initAnimation();
	this->initVariables();
	this->initSprite();
}

Player::~Player()
{
}

void Player::setOverLadder(bool isOverLadder)
{
	this->canClimb = isOverLadder;
}

void Player::setScaleToRight()
{
	this->animatedSprite.setScale(-2.f, 2.f);
}

void Player::setScaleToLeft()
{
	this->animatedSprite.setScale(2.f, 2.f);
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

void Player::updateTexture(sf::Time elapsedTime) {
	if (this->isClimbing) {
		this->currentAnimation = &this->climbAnimation;
		this->animatedSprite.setLooped(true);
	}
	else if (!this->canJump) {
		this->currentAnimation = &this->jumpAnimation;
		this->animatedSprite.setLooped(false);
	}
	else {
		this->animatedSprite.setLooped(true);
		this->currentAnimation = &this->walkingAnimation;
		if (this->isMovingLeft) {
			this->setScaleToLeft();
		}
		else if (this->isMovingRight) {
			this->setScaleToRight();
		}
	}

	this->animatedSprite.play(*currentAnimation);

	if (!this->isMovingUp && !this->isMovingDown && !this->isMovingLeft && !this->isMovingRight) {
		this->animatedSprite.stop();
	}

	this->animatedSprite.update(elapsedTime);
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
	if (this->getBounds().left <= 0.f) {
		//this->alive = false;
		this->setPosition(0.f + this->getBounds().width / 2, this->getBounds().top + this->getBounds().height / 2);
	}
	//Right
	else if (this->getBounds().left + this->getBounds().width >= target->getSize().x) {
		//this->alive = false;
		this->setPosition(target->getSize().x - this->getBounds().width / 2, this->getBounds().top + this->getBounds().height / 2);
	}
	//Top
	if (this->getBounds().top <= 0.f) {
		this->setPosition(this->getPos().x, 0.f);
	}
	//Bottom
	else if (this->getBounds().top + this->getBounds().height >= target->getSize().y) {
		this->alive = false;
		this->setPosition(this->getPos().x, target->getSize().y - this->getBounds().height / 2);
	}
}

void Player::updateMove(sf::Time elapsedTime)
{
	if (this->isClimbing && !this->canClimb) {
		this->isClimbing = false;
		this->velocity.y = 0;
	}
	this->velocity.x = 0.f;
	if (!this->isClimbing) {
		this->velocity.y += 981.f * elapsedTime.asSeconds();
	}
	else {
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
	this->updateTexture(elapsedTime);
}

void Player::move(const float dirX, const float dirY)
{
	this->animatedSprite.move(dirX, dirY);
}

void Player::initTexture()
{
	if (!this->textureWalk.loadFromFile("Media/Textures/mario_walk_anim.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::WALK::Could not load texture file." << "\n";
	}
	if (!this->textureJump.loadFromFile("Media/Textures/mario_jump_anim.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::JUMP::Could not load texture file." << "\n";
	}
	if (!this->textureClimb.loadFromFile("Media/Textures/mario_climb_anim.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::CLIMB::Could not load texture file." << "\n";
	}
}

void Player::initAnimation()
{
	this->walkingAnimation.setSpriteSheet(this->textureWalk);
	this->walkingAnimation.addFrame(sf::IntRect(0, 0, 14, 18));
	this->walkingAnimation.addFrame(sf::IntRect(15, 0, 17, 18));
	this->walkingAnimation.addFrame(sf::IntRect(33, 0, 17, 18));
	this->walkingAnimation.addFrame(sf::IntRect(51, 0, 18, 18));

	this->climbAnimation.setSpriteSheet(this->textureClimb);
	this->climbAnimation.addFrame(sf::IntRect(0, 0, 15, 19));
	this->climbAnimation.addFrame(sf::IntRect(17, 0, 15, 19));


	this->jumpAnimation.setSpriteSheet(this->textureJump);
	this->jumpAnimation.addFrame(sf::IntRect(0, 0, 14, 18));
	this->jumpAnimation.addFrame(sf::IntRect(15, 0, 15, 18));
	this->jumpAnimation.addFrame(sf::IntRect(103, 0, 18, 18));
}

void Player::initVariables()
{
	this->alive = true;
	this->movementSpeed = 100.f;
	this->isMovingUp = false;
	this->isMovingDown = false;
	this->isMovingLeft = false;
	this->isMovingRight = false;
	this->canClimb = false;
	this->isClimbing = false;
	this->canJump = true;
	this->jumpHeight = 50.f;
	this->currentAnimation = &walkingAnimation;
}

void Player::initSprite()
{
	this->animatedSprite = AnimatedSprite(sf::seconds(0.1f), true, true);
	this->animatedSprite.setAnimation(*currentAnimation);
	this->animatedSprite.setOrigin(sf::Vector2f(
		this->getPos().x + this->getBounds().width / 2,
		this->getPos().y + this->getBounds().height / 2
	));
	this->animatedSprite.setScale(2.f, 2.f);
}