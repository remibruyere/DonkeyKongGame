#include "pch.h"
#include "Ladder.h"

Ladder::Ladder()
{
	this->initTexture();
	this->initSprite();
}

Ladder::~Ladder()
{
}

void Ladder::initTexture()
{
	if (!this->texture.loadFromFile("Media/Textures/Echelle.png"))
	{
		std::cout << "ERROR::LADDER::INITTEXTURE::Could not load texture file." << "\n";
	}
}

void Ladder::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.scale(1.1f, 1.85f);
}
