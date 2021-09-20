#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Player
{
private:
	//Shape
	sf::RectangleShape shape;
	
	//Variables	
	float movementSpeed;
	int hpMax;
	int hp;	
	float playerSize;
	float outlineSize;

	//Privare functions
	void initVariables();
	void initShape();

public:
	//Constructors and Distructors
	Player(float x = 0.f, float y = 0.f);
	virtual ~Player();

	//Accessors
	const sf::RectangleShape& getShape() const;
	const int& getHp() const;
	const int& getHpMax() const;

	//Functions
	void takeDamage(const int damage);
	void gainHealth(const int health);

	void updateInput();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

