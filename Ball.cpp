#include "Ball.h"

//Private functions
void Ball::initVariables()
{

}

void Ball::initShape(const sf::RenderWindow& window)
{
	this->shape.setRadius(static_cast<float>(rand() % 10 + 10));

	sf::Color color(255, rand() % 155 + 55, 0, 255);

	switch (this->type)
	{
	case DEFAULT:
		color = sf::Color(rand() % 155 + 55, 0, 255, 255);
		this->shape.setFillColor(color);
		color.r -= 50;
		color.b -= 50;
		break;
	case DAMAGING:
		color = sf::Color(255, rand() % 155 + 55, 0, 255);
		this->shape.setFillColor(color);
		color.r -= 50;
		color.g -= 50;
		break;
	case HEALING:
		color = sf::Color(0, 255, rand() % 155 + 55, 255);
		this->shape.setFillColor(color);
		color.g -= 50;
		color.b -= 50;
		break;
	default:
		break;
	}

	this->shape.setOutlineColor(color);
	this->shape.setOutlineThickness((this->shape.getRadius()) / 4);
	this->shape.setPosition(
		sf::Vector2f(
		static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width),
		static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height)));
}

//Constructors and Distructors
Ball::Ball(const sf::RenderWindow& window, unsigned type)
	: type(type)
{
	this->initShape(window);
}

Ball::~Ball()
{

}

//Accessors
const sf::CircleShape Ball::getShape() const
{
	return this->shape;
}

const int& Ball::getType() const
{
	return this->type;
}

//Functions
void Ball::update()
{

}

void Ball::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}