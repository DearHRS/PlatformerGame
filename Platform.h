#pragma once
#include <SFML/Graphics.hpp>
#include "Collision.h"

class Platform
{
public:
	Platform(std::string texturePath, sf::Vector2f size, sf::Vector2f position);
	Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	Platform();
	~Platform();
	void Draw(sf::RenderWindow& gameWindow);
	Collision GetCollision();

private:
	sf::RectangleShape body;
	sf::Texture texture;
};

