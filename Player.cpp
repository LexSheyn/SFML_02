#include "Player.h"

//Privare functions
void Player::initVariables()
{
	this->movementSpeed = 5.f;
	this->hpMax = 100;
	this->hp = this->hpMax;	
	this->playerSize = 50.f;
	this->outlineSize = this->playerSize / 10.f;
}

void Player::initShape()
{	
	this->shape.setSize(sf::Vector2f(this->playerSize, this->playerSize));
	sf::Color color(0, 220, 0, 255);
	this->shape.setFillColor(color);
	//color.g -= 50;
	//this->shape.setOutlineColor(color);

	//
	//This code changes the player's size, DO NOT USE IT
	//
	//this->shape.setOutlineThickness(this->playerSize / 10.f);
	//

	this->shape.setPosition(sf::Vector2f(560.f, 315.f));
}

//Constructors and Distructors
Player::Player(float x, float y)
{
	this->shape.setPosition(x, y);

	this->initVariables();
	this->initShape();
}

Player::~Player()
{

}

//Accessors
const sf::RectangleShape& Player::getShape() const
{
	return this->shape;
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

//Functions
void Player::takeDamage(const int damage)
{
	if (this->hp > 0)
	{
		this->hp -= damage;
	}

	if (this->hp < 0)
	{
		this->hp = 0;
	}
}

void Player::gainHealth(const int health)
{
	if (this->hp < this->hpMax)
	{
		this->hp += health;
	}

	if (this->hp > this->hpMax)
	{
		this->hp = this->hpMax;
	}
}


void Player::updateInput()
{
	//Keybiard input
	//Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //Left
	{
		this->shape.move(-this->movementSpeed, 0.f);
	}//Right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->shape.move(this->movementSpeed, 0.f);
	}
	//Up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->shape.move(0.f, -this->movementSpeed);
	}//Down
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->shape.move(0.f, this->movementSpeed);
	}
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	//Left
	if (this->shape.getGlobalBounds().left <= 0.f)
	{
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
	}
	
	//Right
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
	{
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
	}
	
	//Top
	if (this->shape.getGlobalBounds().top <= 0.f)
	{
		this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);
	}
	
	//Bottom
	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
	{
		this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
	}
}

void Player::update(const sf::RenderTarget* target)
{
	this->updateInput();

	//Window bounds collision
	this->updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}






