#include "pch.h"
#include "StringHelpers.h"
#include "Game.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initGUI();
	this->initWorld();
	this->initDonkey();
	this->initPlayer();
	this->initStatistics();
}

Game::~Game()
{
	delete this->window;
}

/******* RUN ********/

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
			if (this->player->alive)
				update(TimePerFrame);
		}

		updateCollisions();
		updateStatistics(elapsedTime);
		render();
	}
}

/******* EVENT ********/

void Game::processEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape) {
				this->initPlayer();
			}
			else {
				this->player->updateInput(this->ev.key.code, true);
			}
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

/******* UPDATE ********/

void Game::update(sf::Time elapsedTime)
{
	this->donkey->spawnBarrel(elapsedTime, this->barrels);
	for (Barrel* barrel : this->barrels) {
		barrel->update(elapsedTime);
	}
	this->donkey->update(elapsedTime);
	this->player->update(elapsedTime);
}

void Game::updateCollisions()
{
	for (Barrel* barrel : this->barrels) {
		for (Block* block : this->blocks) {
			if (block->getBounds().intersects(barrel->getBounds())) {
				if (barrel->getPos().y < block->getPos().y) {
					barrel->setPosition(barrel->getPos().x, block->getPosTop().y - barrel->getBounds().height / 2);
					barrel->OnCollision(sf::Vector2f(0.f, -1.f));
				}
				else {
					barrel->setPosition(barrel->getPos().x, block->getPosBottom().y + barrel->getBounds().height / 2);
					barrel->OnCollision(sf::Vector2f(0.f, 1.f));
				}
				break;
			}
		}
	}
	for (Ladder* ladder : this->ladders) {
		if (ladder->getBounds().contains(this->player->getPos()) || ladder->getBounds().contains(this->player->getPosBottom())) {
			this->player->setOverLadder(true);
			break;
		}
		this->player->setOverLadder(false);
	}
	for (Barrel* barrel : this->barrels) {
		if (barrel->getBounds().intersects(this->player->getBounds()) || barrel->getBounds().intersects(this->player->getBounds())) {
			this->player->alive = false;
			break;
		}
	}
	if (!this->player->isClimbing) {
		for (Block* block : this->blocks) {
			if (block->getBounds().intersects(this->player->getBounds())) {
				//Player middle above block middle
				if (this->player->getPos().y < block->getPos().y) {
					this->player->setPosition(this->player->getPos().x, block->getPosTop().y - this->player->getBounds().height / 2);
					this->player->OnCollision(sf::Vector2f(0.f, -1.f));
				}
				//Player middle under block middle
				else {
					this->player->setPosition(this->player->getPos().x, block->getPosBottom().y + this->player->getBounds().height / 2);
					this->player->OnCollision(sf::Vector2f(0.f, 1.f));
				}
				//std::cout << "collision block" << std::endl;
				break;
			}
		}
	}
	for (Barrel* barrel : this->barrels) {
		barrel->updateWindowBoundsCollision(this->window);
	}
	this->barrels.erase(
		std::remove_if(
			this->barrels.begin(),
			this->barrels.end(),
			[this](Barrel* barrel) {
				return barrel->isOutOfWindow(this->window);
			}
		),
		this->barrels.end());
	this->player->updateWindowBoundsCollision(this->window);
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	this->mStatisticsUpdateTime += elapsedTime;
	this->mStatisticsNumFrames += 1;

	if (this->mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		this->mStatisticsText.setString(
			"Frames / Second = " + toString(this->mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(this->mStatisticsUpdateTime.asMicroseconds() / this->mStatisticsNumFrames) + "us");

		this->mStatisticsUpdateTime -= sf::seconds(1.0f);
		this->mStatisticsNumFrames = 0;
	}
}

/******* RENDER ********/

void Game::renderGUI()
{
	this->window->draw(this->pointText);
}

void Game::render()
{
	this->window->clear(sf::Color(255, 255, 255, 1));

	for (Entity* entity : this->entities) {
		entity->render(*(this->window));
	}

	for (Block* block : this->blocks) {
		block->render(*(this->window));
	}

	for (Ladder* ladder : this->ladders) {
		ladder->render(*(this->window));
	}

	for (Barrel* barrel : this->barrels) {
		barrel->render(*(this->window));
	}

	this->donkey->render(*(this->window));
	this->player->render(*(this->window));

	this->renderGUI();
	this->window->draw(mStatisticsText);

	if (!this->player->alive)
		this->window->draw(this->gameOverText);

	this->window->display();
}

/******* INIT ********/

void Game::initVariables()
{
	this->window = nullptr;
	this->mStatisticsNumFrames = 0;
	this->mStatisticsUpdateTime = sf::seconds(0.f);
}

void Game::initWindow()
{
	this->videoMode.height = 800;
	this->videoMode.width = 600;

	this->window = new sf::RenderWindow(this->videoMode, "DonkeyKong", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
	if (!this->mFont.loadFromFile("Media/Sansation.ttf"))
		std::cout << "ERROR::GAME::Failed to load font Sansation" << std::endl;
	if (!this->font.loadFromFile("Media/PixellettersFull.ttf"))
		std::cout << "ERROR::GAME::Failed to load font PixellettersFull" << std::endl;
}

void Game::initWorld()
{
	this->initBlocks();
	this->initLadders();
	
	for (int i = 0; i < 2; ++i) {
		for (int y = 0; y < 2; ++y) {
			StaticBarrel* staticBarrel = new StaticBarrel();
			staticBarrel->setPosition(
				staticBarrel->getBounds().width / 2 + staticBarrel->getBounds().width * i + 1,
				330 - staticBarrel->getBounds().height - staticBarrel->getBounds().height * y);
			this->entities.push_back(staticBarrel);
		}
	}
}

void Game::initGUI()
{
	//Init point text
	this->pointText.setPosition(700.f, 25.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("test");

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(150);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);
}

void Game::initBlocks()
{
	Block* block = new Block();
	float blockWidth = block->getBounds().width;
	float blockHeight = block->getBounds().height;
	delete block;
	// Height max : 800 | Width max : 600
	float ladderPositions[8][2][2] = {
		{{0,330}, {380,330}},
		{{380,330}, {550,350}},
		{{40,440}, {600,410}},
		{{0,500}, {550,515}},
		{{40,620}, {600,590}},
		{{0,680}, {550,710}},
		{{300,800}, {600,770}},
		{{0,800}, {300,800}}
	};
	for (int i = 0; i < 8; ++i) {
		int numberBlock = abs(int(round((ladderPositions[i][0][0] - ladderPositions[i][1][0]) / blockWidth)));
		float stepHeight = -((ladderPositions[i][0][1] - ladderPositions[i][1][1]) / (blockHeight));
		for (int j = 0; j < numberBlock; ++j) {
			Block* block = new Block();
			block->setPosition(
				ladderPositions[i][0][0] + block->getBounds().width / 2 + block->getBounds().width * j,
				ladderPositions[i][0][1] - block->getBounds().height / 2 + stepHeight * j);
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
			BLOCK_SPACE * (i + 1) + ladder->getBounds().height / 2 + 1.f);
		this->ladders.push_back(ladder);
	}
}

void Game::initDonkey()
{
	this->donkey = new Donkey();
	this->donkey->setPosition(
		50.f + this->donkey->getBounds().width / 2,
		311 - this->donkey->getBounds().height / 2
	);
}

void Game::initPlayer()
{
	this->player = new Player();
	this->player->setPosition(
		80.f + this->player->getBounds().width / 2,
		BLOCK_SPACE * 5 - this->player->getBounds().height / 2
	);
}

void Game::initStatistics()
{
	mStatisticsText.setString("Welcome to Donkey Kong 1981");
	mStatisticsText.setFont(this->mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
}