#include "Game.h"

// Initializers

void Game::initVariables()
{
	this->window = nullptr;
	this->currentTilePath = this->emptyTilePath;
}

void Game::initWindow()
{
	this->videoMode.height = 625;
	this->videoMode.width = 1400;
	this->window = new sf::RenderWindow(this->videoMode, "C++ Drawing Table");

}

void Game::initFPS()
{
	this->clock = sf::Clock::Clock();
	this->previousTime = clock.getElapsedTime();

	this->font.loadFromFile("./resources/pixelmix.ttf");
	this->fpsText.setCharacterSize(20);
	this->fpsText.setFont(this->font);
	this->fpsText.setString("-- FPS");
}
void Game::initCells()
{
	int xPos = 0;
	int yPos = 0;
	for (int x = 0;x < XMAX;x++) {
		for (int y = 0;y < YMAX;y++) {
			this->map[x][y].textureLoader.loadFromFile(this->emptyTilePath);
			this->map[x][y].sprite.setTexture(this->map[x][y].textureLoader);
			this->map[x][y].sprite.setScale(5, 5);
			this->map[x][y].sprite.setPosition(xPos, yPos);
			yPos = yPos + 25;
		}
		yPos = 0;
		xPos = xPos + 25;
	}

}

void Game::initOptions()
{
	int yPos = 0;

	for (int x = 0;x < NCOLORS;x++) {
		this->colorOptions[x].textureLoader.loadFromFile(this->colorList[x]);
		this->colorOptions[x].sprite.setTexture(this->colorOptions[x].textureLoader);
		this->colorOptions[x].sprite.setScale(10, 10);
		this->colorOptions[x].sprite.setPosition(1300, yPos);
		yPos += 50;
	}
	this->selector.textureLoader.loadFromFile(this->selectTilePath);
	this->selector.sprite.setTexture(this->selector.textureLoader);
	this->selector.sprite.setScale(10, 10);
	this->selector.sprite.setPosition(1300, 1600);


}



// Constructors | Destructors

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFPS();
	this->initCells();
	this->initOptions();
}

Game::~Game()
{
	delete this->window;
	delete this->map;
	
	
}


// Accessors

const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape) {
				this->window->close();
			}
			break;
		default:
			break;
		}
		
		
	}
}

void Game::renderCells()
{
	for (int x = 0;x < XMAX;x++) {
		for (int y = 0; y < YMAX;y++) {
			this->window->draw(this->map[x][y].sprite);
		}
	}
	
}

void Game::renderOptions()
{
	for (int x = 0;x < NCOLORS;x++) {
		this->window->draw(this->colorOptions[x].sprite);

	}
	this->window->draw(this->selector.sprite);
}

void Game::checkClick()
{
	

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{		
		this->checkSprite();
		
	}
	
}
void Game::checkSprite()
{
	for (int x = 0;x < XMAX;x++) {
		for (int y = 0; y < YMAX;y++) {
			if (this->map[x][y].sprite.getGlobalBounds().contains(this->mousePosView))
			{
				this->map[x][y].textureLoader.loadFromFile(this->currentTilePath);
				break;
			}
		}
	}
	for(int x = 0; x<NCOLORS;x++){
		if (this->colorOptions[x].sprite.getGlobalBounds().contains(this->mousePosView))
		{
			if (x == NCOLORS - 1) {
				this->fillSprites();
			}
			else {
				
				this->selector.sprite.setPosition(1300, this->colorOptions[x].sprite.getPosition().y);
				this->currentTilePath = this->colorList[x];
			}
			
			break;
		}
	}
}
void Game::fillSprites()
{
	for (int x = 0;x < XMAX;x++) {
		for (int y = 0;y < YMAX;y++) {
			this->map[x][y].textureLoader.loadFromFile(this->currentTilePath);
		}
	}
}
void Game::updateMousePositions()
{
	this->mouserPosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mouserPosWindow);
	this->checkClick();

}




// Functions

void Game::update()
{
	// Calculate FPS
	this->currentTime = this->clock.getElapsedTime();
	this->fps = 1.0f / (this->currentTime.asSeconds() - this->previousTime.asSeconds());
	this->fpsText.setString(std::to_string(int(floor(this->fps))) + " FPS");
	this->previousTime = this->currentTime;

	this->pollEvents();
	this->updateMousePositions();

}

void Game::render()
{
	// Clear last frame
	this->window->clear(sf::Color::Black);
	// Draw
	this->window->draw(this->fpsText);
	this->renderCells();
	this->renderOptions();
	// Display in Screen
	this->window->display();
}
