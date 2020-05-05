#pragma once

enum EntityType
{
	player,
	block,
	echelle
};

class Entity
{
public:
	Entity();
	~Entity();

	//Accessor
	const sf::Vector2f& getPos() const;
	const sf::Vector2f getPosMiddle() const;
	const sf::FloatRect getBounds() const;

	//Modifiers
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);

	void render(sf::RenderTarget& target);

private:
	virtual void initTexture() = 0;
	virtual void initSprite() = 0;

public:
	sf::Sprite sprite;
	sf::Texture texture;
};

