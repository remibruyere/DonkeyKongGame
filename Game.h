#pragma once

#include "Player.h"
#include "Ladder.h"
#include "Block.h"
#include "Donkey.h"
#include "Barrel.h"
#include "Entity.h"
#include "StaticBarrel.h"

#define LADDER_COUNT 4
#define BLOCK_COUNT_X 8
#define BLOCK_COUNT_Y 5
#define BLOCK_SPACE 150.f

class Game
{
public:
	Game();
	virtual ~Game();
	void run();

public:
	sf::RenderWindow* window;

private:
	void processEvents();
	void update(sf::Time elapsedTime);
	void updateCollisions();
	void updateStatistics(sf::Time elapsedTime);
	void renderGUI();
	void render();

	void initVariables();
	void initWindow();
	void initFonts();
	void initWorld();
	void initGUI();
	void initBlocks();
	void initLadders();
	void initDonkey();
	void initPlayer();
	void initStatistics();

private:
	static const sf::Time TimePerFrame;

	//Window
	sf::VideoMode videoMode;
	sf::Event ev;

	//Game objects
	sf::Font	mFont;
	sf::Text	mStatisticsText;
	sf::Time	mStatisticsUpdateTime;
	std::size_t	mStatisticsNumFrames;

	//World
	std::vector<Entity*> entities;

	//GUI
	sf::Font font;
	sf::Text pointText;

	sf::Text gameOverText;

	//Player
	Player* player;

	//Donkey
	Donkey* donkey;

	//Blocks
	std::vector<Block*> blocks;

	//Ladders
	std::vector<Ladder*> ladders;

	//Barrels
	std::vector<Barrel*> barrels;
};

