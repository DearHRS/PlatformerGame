#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collision.h"

class Player
{
public:
	Player(float hitPoints, std::string texturePath, sf::Vector2u spriteCount, float spriteLifeTime, float speed, float jumpHeight);
	~Player();

	void Update(float deltatime);									    //updates player based on input
	void Draw(sf::RenderWindow& gameWindow);		//draws player
	void OnColliosion(sf::Vector2f direction);					//redundant atm
	void AllowJump(bool allow);										//function to set manipulate canJump
	void TakesDamage(float amountTaken);					//function to decrease hitpoints;
	void SetLife(int lifeAmount);										//public function to restore life of player
	int GetLife();
	float GetScore();
	void SetScore(float score);
	void SetPosition(sf::Vector2f position);

	sf::Vector2f GetPosition();
	Collision GetCollision();

private:
	float hitPoints;
	int life;
	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;
	float speed;

	float score;

	sf::Texture texture;
	sf::RectangleShape hitBox;                                    //actual player size
	sf::RectangleShape animationArea;                                       //animation area of player
	Animation animation;
	unsigned int spriteRow;	
	bool isFacingRight;		
};

