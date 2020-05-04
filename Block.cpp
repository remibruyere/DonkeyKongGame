#include "pch.h"
#include "Block.h"

Block::Block()
{
	this->initTexture();
	this->initSprite();
}

Block::~Block()
{
}

void Block::initTexture()
{
	if (!this->texture.loadFromFile("Media/Textures/Block.png"))
	{
		std::cout << "ERROR::BLOCK::INITTEXTURE::Could not load texture file." << "\n";
	}
}

void Block::initSprite()
{
	this->sprite.setTexture(this->texture);
	//this->sprite.scale(0.1f, 0.1f);
}
