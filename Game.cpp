#include "pch.h"
#include "StringHelpers.h"
#include "Game.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initTextures();
	this->initBlocks();
	this->initLadders();
	this->initPlayer();
	this->initStatistics();
}

Game::~Game()
{
	delete this->window;
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (this->window->isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}

		updateCollisions();
		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::KeyPressed:
			this->player->updateInput(this->ev.key.code, true);
			break;

		case sf::Event::KeyReleased:
			this->player->updateInput(this->ev.key.code, false);
			break;

		case sf::Event::Closed:
			this->window->close();
			break;
		}
	}
}

void Game::update(sf::Time elapsedTime)
{
	this->player->update(elapsedTime);
}

void Game::updateCollisions()
{
	this->player->updateWindowBoundsCollision(this->window);
	for (Ladder* ladder : this->ladders) {
		if (ladder->getBounds().contains(this->player->getPosMiddle()) || ladder->getBounds().contains(this->player->getPosMiddleBottom())) {
			this->player->setOverLadder(true);
			break;
		}
		this->player->setOverLadder(false);
	}
	if (!this->player->isClimbing) {
		for (Block* block : this->blocks) {
			if (block->getBounds().intersects(this->player->getBounds())) {
				if (this->player->getPosMiddle().y < block->getPosMiddle().y) {
					this->player->setPosition(this->player->getPos().x, block->getPos().y - this->player->getBounds().height);
					this->player->OnCollision(sf::Vector2f(0.f, -1.f));
				}
				else {
					this->player->setPosition(this->player->getPos().x, block->getPos().y + block->getBounds().height);
					this->player->OnCollision(sf::Vector2f(0.f, 1.f));
				}
				break;
			}
		}
	}
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Game::render()
{
	this->window->clear();

	for (Block* block : this->blocks) {
		block->render(*(this->window));
	}

	for (Ladder* ladder : this->ladders) {
		ladder->render(*(this->window));
	}

	this->player->render(*(this->window));

	this->window->draw(mStatisticsText);
	this->window->display();
}

void Game::initVariables()
{
	this->window = nullptr;
	this->mStatisticsNumFrames = 0;
}

void Game::initWindow()
{
	this->videoMode.height = 800;
	this->videoMode.width = 840;

	this->window = new sf::RenderWindow(this->videoMode, "DonkeyKong", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::initTextures()
{
	mFont.loadFromFile("Media/Sansation.ttf");
}

void Game::initBlocks()
{
	for (int i = 0; i < BLOCK_COUNT_X; i++)
	{
		for (int j = 0; j < BLOCK_COUNT_Y; j++)
		{
			Block* block = new Block();
			block->setPosition(
				80.f + 70.f * (i + 1),
				BLOCK_SPACE * (j + 1));
			this->blocks.push_back(block);
		}
	}
}

void Game::initLadders()
{
	for (int i = 0; i < LADDER_COUNT; i++)
	{
		Ladder* ladder = new Ladder();
		ladder->setPosition(
			80.f + 70.f * (i + 1),
			BLOCK_SPACE * (i + 1) + 1.f);
		this->ladders.push_back(ladder);
	}
}

void Game::initPlayer()
{
	this->player = new Player();
	this->player->setPosition(
		80.f + 70.f,
		BLOCK_SPACE * 5 - this->player->getBounds().height
	);
}

void Game::initStatistics()
{
	mStatisticsText.setString("Welcome to Donkey Kong 1981");
	mStatisticsText.setFont(this->mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
}