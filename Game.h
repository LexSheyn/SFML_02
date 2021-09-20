#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>
#include <string>

#include "Player.h"
#include "Ball.h"

class Game
{
private:	
	//Window
	sf::VideoMode videoMode;
	sf::RenderWindow* window;	
	sf::Event sfmlEvent;
	bool endGame;

	//Game objects
	Player player;
	std::vector<Ball> balls;
	sf::Font guiFont;
	std::string guiFontName = "../Fonts/PixellettersFull.ttf";
	sf::Font endGameFont;
	std::string endGameFontName = "../Fonts/defused.ttf";
	sf::Text guiText;
	sf::Text endGameText;

	//Variables	
	float spawnTimerMax;
	float spawnTimer;
	unsigned maxBalls;
	int damagingBallsMax;
	int damagingBalls;
	int healingBallsMax;
	int healingBalls;
	unsigned points;

	//Private functions
	void initVariables();
	void initWindow();
	//void initFonts(sf::Font* font , std::string* fontName);
	void initGuiFont();
	void initEndGameFont();
	void initGuiText();
	void initEndGameText();

public:
	//Constructors and Distructors
	Game();
	~Game();

	//Accessors
	const bool& getEndGame() const;

	//Modifiers


	//Functins
	const bool running() const;
	void pollEvents();

	const int randBallType() const;
	void spawnBalls();
	void updatePlayer();
	void updateCollision();
	void updateGuiText();
	void updateEndGameText();
	void update();

	void renderGuiText(sf::RenderTarget* target);
	void render();
};

