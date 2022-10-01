#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <string>
#include "Collision.h"

class Coins
{
public:
	Coins();
	Coins(float value, unsigned int valueSize, sf::Vector2f offSet, std::string fontPath, sf::Vector2f position, sf::Vector2f hitBoxSize, std::string texturePath, sf::Vector2u spriteCount, float spriteLifeTime);
	Coins(float value, unsigned int valueSize, sf::Vector2f offSet, sf::Font* font, sf::Vector2f position, sf::Vector2f hitBoxSize, sf::Texture* texture, sf::Vector2u spriteCount, float spriteLifeTime);
	~Coins();
	void Update(float deltatime);
	void Draw(sf::RenderWindow& gameWindow);
	float GetScore();
	void Collected(bool yes);
	Collision GetCollision();

private:
	sf::RectangleShape animationArea;
	sf::RectangleShape hitBox;
	sf::Image textureImage;
	sf::Texture texture;
	Animation animation;
	sf::Font font;
	sf::Text text;
	
	float value;
	bool isCollected = false;
};

