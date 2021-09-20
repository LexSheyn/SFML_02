#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum BallType {DEFAULT = 0, DAMAGING, HEALING, NROFTYPES};

class Ball
{
private:
	//Shape
	sf::CircleShape shape;

	//Variables
	unsigned type;

	//Private functions
	void initVariables();
	void initShape(const sf::RenderWindow& window);

public:
	//Constructors and Distructors
	Ball(const sf::RenderWindow& window, unsigned type);
	virtual ~Ball();

	//Accessors
	const sf::CircleShape getShape() const;
	const int& getType() const;

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

