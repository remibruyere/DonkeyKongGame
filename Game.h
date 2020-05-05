#pragma once

#include "Player.h"
#include "Ladder.h"
#include "Block.h"

#define LADDER_COUNT 4
#define BLOCK_COUNT_X 8
#define BLOCK_COUNT_Y 5
#define BLOCK_SPACE 110.f

class Game
{
public:
	Game();
	virtual ~Game();
	void run();

private:
	void processEvents();
	void update(sf::Time elapsedTime);
	void updateCollisions();
	void updateStatistics(sf::Time elapsedTime);
	void render();

	void initVariables();
	void initWindow();
	void initTextures();
	void initBlocks();
	void initLadders();
	void initPlayer();
	void initStatistics();

private:
	static const sf::Time TimePerFrame;

	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Game objects
	sf::Font	mFont;
	sf::Text	mStatisticsText;
	sf::Time	mStatisticsUpdateTime;
	std::size_t	mStatisticsNumFrames;

	//Player
	Player* player;

	//Blocks
	std::vector<Block*> blocks;

	//Ladders
	std::vector<Ladder*> ladders;
};

