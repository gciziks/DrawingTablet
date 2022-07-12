#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include <vector>

const int XMAX = 50;
const int YMAX = 25;
const int NCOLORS = 11;

class Game
{


	private:
		// SFML Variables
		sf::RenderWindow* window;
		sf::Event ev;
		sf::VideoMode videoMode;

		//Handles FPS Calculus
		sf::Font font;
		sf::Text fpsText;
		sf::Clock clock;
		sf::Time previousTime;
		sf::Time currentTime;
		float fps;

		//Sprite Files
		std::string emptyTilePath = "./resources/MapTile.png";
		std::string fillTilePath = "./resources/FillTile.png";
		std::string selectTilePath = "./resources/SelectTile.png";
		std::string currentTilePath;

		std::string redTilePath = "./resources/RedTile.png";
		std::string yellowTilePath = "./resources/YellowTile.png";
		std::string purpleTilePath = "./resources/PurpleTile.png";
		std::string pinkTilePath = "./resources/PinkTile.png";
		std::string orangeTilePath = "./resources/OrangeTile.png";
		std::string greenTilePath = "./resources/GreenTile.png";
		std::string cyanTilePath = "./resources/CyanTile.png";
		std::string blueTilePath = "./resources/BlueTile.png";
		std::string blackTilePath = "./resources/BlackTile.png";
		std::vector<std::string> colorList = {redTilePath,yellowTilePath,purpleTilePath,pinkTilePath,orangeTilePath,greenTilePath,cyanTilePath,blueTilePath,blackTilePath,emptyTilePath,fillTilePath };

		//Mouse Positions
		sf::Vector2i mouserPosWindow;
		sf::Vector2f mousePosView;
		bool mouseHeld;

		// Structures
		struct point {
			sf::Texture textureLoader;
			sf::Sprite sprite;
		};

		// Vars
		point (*map)[YMAX] = new point[XMAX][YMAX];
		point (*colorOptions) = new point[NCOLORS];
		point selector;
		

		// Initializers

		void initVariables();
		void initWindow();
		void initFPS();
		void initCells();
		void initOptions();

		//Functions
		void renderCells();
		void renderOptions();
		void checkClick();
		void checkSprite();
		void fillSprites();
		void updateMousePositions();



	public:

		//Constructors | Desctructors
		Game();
		virtual ~Game();

		//Accessors
		const bool getWindowIsOpen() const;

		// Functions
		void pollEvents();
		

		// Main Functions
		void update();
		void render();
};

