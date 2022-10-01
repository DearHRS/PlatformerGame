#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"


class Button
{
public:
	Button();
	Button(std::string texturePath, std::string fontPath, std::string text, unsigned int textSize, sf::Vector2f textOffSet, sf::Vector2f buttonSize, sf::Vector2f buttonPosition, sf::Vector2u spriteCount, float spriteCurrentTime);
	~Button();

	void Update(float deltaTime, sf::Vector2i mousePosition, float& gamemode, float destination);
	void Draw(sf::RenderWindow& gameWindow);
	sf::Vector2f GetPosition();


private:
	sf::Texture texture;
	sf::RectangleShape body;
	Animation animation;
	sf::Text text;
	sf::Font font;
};

