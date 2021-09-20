#include "Game.h"

//Private functions
void Game::initVariables()
{
	this->endGame = false;
	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxBalls = 12;
	this->damagingBallsMax = 3;
	this->damagingBalls = 0;
	this->healingBallsMax = 2;
	this->healingBalls = 0;
	this->points = 0;
}

void Game::initWindow()
{
	//this->videoMode = sf::VideoMode::getDesktopMode();
	this->videoMode = sf::VideoMode(1120, 630);
	this->window = new sf::RenderWindow(this->videoMode, "Game 02", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initGuiFont()
{
	if (!this->guiFont.loadFromFile(this->guiFontName))
	{
		std::cout << "ERROR::GAME::INITFONTS::FAILED TO LOAD: " << guiFontName << "\n";
	}
}

void Game::initEndGameFont()
{
	if (!this->endGameFont.loadFromFile(this->endGameFontName))
	{
		std::cout << "ERROR::GAME::INITFONTS::FAILED TO LOAD: " << endGameFontName << "\n";
	}
}

void Game::initGuiText()
{
	//GUI text initialization
	this->guiText.setFont(guiFont);
	this->guiText.setPosition(sf::Vector2f(10.f, 10.f));
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setOutlineColor(sf::Color::Black);
	this->guiText.setOutlineThickness(1.f);
	this->guiText.setCharacterSize(24);
	this->guiText.setString("None");
}

void Game::initEndGameText()
{
	//End game text initialization
	this->endGameText.setFont(endGameFont);
	this->endGameText.setPosition(sf::Vector2f((this->window->getSize().x)*2/8, (this->window->getSize().y)*2/6));
	this->endGameText.setFillColor(sf::Color::Red);
	//this->endGameText.setOutlineColor(sf::Color::Black);
	//this->endGameText.setOutlineThickness(1);
	this->endGameText.setCharacterSize(60);
	this->endGameText.setString("None");
}

//Constructors and Distructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initGuiFont();
	this->initEndGameFont();
	this->initGuiText();
	this->initEndGameText();
}

Game::~Game()
{
	delete this->window;
}

//Accessors
const bool& Game::getEndGame() const
{
	return this->endGame;
}

//Modifiers


//Functions
const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->sfmlEvent))
	{
		switch (this->sfmlEvent.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
			break;
		}
	}
}

const int Game::randBallType() const
{
	int type = BallType::DEFAULT;

	int randValue = rand() % 100 + 1;

	if (randValue > 20 && randValue < 80)
	{
		type = BallType::DAMAGING;
	}
	else if (randValue > 80 && randValue <= 100)
	{
		type = BallType::HEALING;
	}

	return type;
}

void Game::spawnBalls()
{
	//Timer
	if (this->spawnTimer < this->spawnTimerMax)
	{
		this->spawnTimer += 1.f;
	}
	else
	{
		if (this->balls.size() < this->maxBalls)
		{			
			switch (this->randBallType())
			{
			case BallType::DEFAULT:
				this->balls.push_back(Ball(*this->window, BallType::DEFAULT));
				break;
			case BallType::DAMAGING:
				//if (this->damagingBalls < this->damagingBallsMax)
				//{
					this->balls.push_back(Ball(*this->window, BallType::DAMAGING));
					//this->damagingBalls++;
				//}
				//else
				//{
					//this->balls.push_back(Ball(*this->window, BallType::DEFAULT));
				//}				
				break;
			case BallType::HEALING:
				if (this->healingBalls < this->healingBallsMax)
				{
					this->balls.push_back(Ball(*this->window, BallType::HEALING));
					this->healingBalls++;
				}
				else
				{
					this->balls.push_back(Ball(*this->window, BallType::DEFAULT));
				}				
				break;
			default:
				break;
			}
			
			//this->balls.push_back(Ball(*this->window, this->randBallType()));

			this->spawnTimer = 0.f;
		}		
	}
}

void Game::updatePlayer()
{
	this->player.update(this->window);

	if (this->player.getHp() <= 0)
	{
		this->endGame = true;
	}
}

void Game::updateCollision()
{
	//Check the collision
	for (size_t i = 0; i < this->balls.size(); i++)
	{
		if (this->player.getShape().getGlobalBounds().intersects(this->balls[i].getShape().getGlobalBounds()))
		{
			switch (this->balls[i].getType())
			{
			case BallType::DEFAULT:
				//Add points
				this->points += rand() % 10 + 10;
				break;
			case BallType::DAMAGING:
				this->player.takeDamage(rand() % 20 + 20);
				//this->damagingBalls--;
				break;
			case BallType::HEALING:
				this->player.gainHealth(rand() % 10 + 1);
				this->healingBalls--;
				break;
			default:
				break;
			}

			//Remove the ball
			this->balls.erase(this->balls.begin() + i);
			
		}
	}	
}

void Game::updateGuiText()
{
	std::stringstream ss;

	ss << "Points:"
	   << " " << this->points << "\n"
	   << "Health:"
	   << " " << this->player.getHp() << "|" << this->player.getHpMax() << "\n";

	this->guiText.setString(ss.str());
}

void Game::updateEndGameText()
{
	std::stringstream ss;

	ss << "GAME OVER" << "\n";

	this->endGameText.setString(ss.str());

}

void Game::update()
{
	this->pollEvents();

	if (this->endGame == false)
	{
		this->spawnBalls();
		this->updatePlayer();
		this->updateCollision();
		this->updateGuiText();
		this->updateEndGameText();
	}
}

void Game::renderGuiText(sf::RenderTarget* target)
{
	target->draw(this->guiText);
}

void Game::render()
{
	this->window->clear();

	//Render stuff
	this->player.render(this->window);

	for (auto i : this->balls)
	{
		i.render(*this->window);
	}

	//Render GUI
	this->renderGuiText(this->window);

	//Render end game text
	if (this->endGame == true)
	{
		this->window->draw(this->endGameText);
	}

	this->window->display();
}