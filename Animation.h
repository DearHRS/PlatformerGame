#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
private:
	sf::Vector2u spriteCount;		//total sprites from sprite sheet
	sf::Vector2u spriteCurrent;		//current sprite count from sprite sheet
	float spriteLifeTime;				//total time how long 1 sprite is displayed on screen
	float spriteCurrentTime;			//animation cycle counter


public:
	sf::IntRect textureRect;			//texture size related object from sfml class
	Animation();
	Animation(sf::Texture* texture, sf::Vector2u spriteCount, float spriteCurrentTime);
	~Animation();
	void Update(int spriteRow, float deltaTime, bool isFacingRight);
};

